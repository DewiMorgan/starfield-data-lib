#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <set>

#include <mysql/mysql.h>
#include "parser.h"
#include "schema.h"
#include "vfs.h"
#include "ba2_stream.h"

namespace fs = std::filesystem;

bool g_dryRun = false;

std::string getTimestamp() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm_struct;
    localtime_r(&now, &tm_struct);
    char buf[10];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm_struct);
    return std::string(buf);
}

void log(const std::string& msg, bool isError = false) {
    if (isError) {
        std::cerr << "[" << getTimestamp() << "] " << msg << std::endl;
    } else {
        std::cout << "[" << getTimestamp() << "] " << msg << std::endl;
    }
}

struct DbConfig {
    std::string host;
    std::string user;
    std::string pass;
    std::string db;
};

DbConfig get_db_config() {
    return {
        getenv("MYSQL_HOST") ? getenv("MYSQL_HOST") : "localhost",
        getenv("MYSQL_USER") ? getenv("MYSQL_USER") : "root",
        getenv("MYSQL_PASS") ? getenv("MYSQL_PASS") : "",
        getenv("MYSQL_DB") ? getenv("MYSQL_DB") : "starfield"
    };
}

void execute_query(MYSQL* conn, const std::string& query) {
    if (g_dryRun) {
        log("[Dry Run] Skipping query: " + query);
        return;
    }
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "[" << getTimestamp() << "] MySQL Error: " << mysql_error(conn) << "\nQuery: " << query << std::endl;
    }
}

void indexAsset(MYSQL* conn, int source_id, const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) {
    auto esc = [](std::string s) {
        size_t pos = 0;
        while ((pos = s.find("'", pos)) != std::string::npos) {
            s.replace(pos, 1, "''");
            pos += 2;
        }
        return s;
    };
    std::string q = "INSERT IGNORE INTO assets (source_id, virtual_path, literal_path, internal_path, size) VALUES (" + 
                   (source_id == -1 ? "NULL" : std::to_string(source_id)) + "," + 
                   "'" + esc(virtual_path) + "'," + 
                   "'" + esc(literal_path) + "'," + 
                   "'" + esc(internal_path) + "'," + 
                   std::to_string(size) + ")";
    execute_query(conn, q);
}

void index_plugin_stream(MYSQL* conn, int plugin_id, IReadStream* stream, const std::string& path, int& assetsCount) {
    uint64_t current_offset = 0;
    std::vector<std::string> record_batch;
    std::vector<std::string> edid_batch;
    int count = 0;

    while (true) {
        RecordHeader header;
        size_t readBytes = stream->read(&header, sizeof(RecordHeader));
        if (readBytes < sizeof(RecordHeader)) break;

        std::string sig(header.sig, 4);
        if (g_RecordSchemas.find(sig) == g_RecordSchemas.end()) {
            break;
        }

        std::vector<uint8_t> data(header.dataSize);
        if (stream->read(data.data(), header.dataSize) < header.dataSize) break;

        char escaped_sig[10]; 
        mysql_real_escape_string(conn, escaped_sig, sig.c_str(), 4);
        
        std::string rec_val = "(" + std::to_string(plugin_id) + "," + 
                             std::to_string(current_offset) + "," + 
                             std::to_string(header.formId) + ",'" + 
                             std::string(escaped_sig) + "'," + 
                             std::to_string(header.dataSize) + ")";
        record_batch.push_back(rec_val);

        StarfieldRecord record = Parser::parseRecord(data.data(), data.size(), header, current_offset);
        std::string edid_val = record.getTlvString("EDID");
        if (!edid_val.empty()) {
            std::string edid_esc = edid_val; 
            size_t pos = 0;
            while ((pos = edid_esc.find("'", pos)) != std::string::npos) {
                edid_esc.replace(pos, 1, "''");
                pos += 2;
            }
            edid_batch.push_back("(" + std::to_string(plugin_id) + "," + 
                                std::to_string(current_offset) + ",'" + 
                                edid_esc + "')");
        }

        count++;
        current_offset += sizeof(RecordHeader) + header.dataSize;

        if (record_batch.size() >= 1000) {
            std::string q = "INSERT IGNORE INTO records (source_id, offset, formid, signature, size) VALUES ";
            for (size_t i = 0; i < record_batch.size(); ++i) {
                q += record_batch[i] + (i == record_batch.size() - 1 ? "" : ",");
            }
            execute_query(conn, q);
            record_batch.clear();
        }

        if (edid_batch.size() >= 1000) {
            std::string q = "INSERT IGNORE INTO edids (source_id, offset, edid) VALUES ";
            for (size_t i = 0; i < edid_batch.size(); ++i) {
                q += edid_batch[i] + (i == edid_batch.size() - 1 ? "" : ",");
            }
            execute_query(conn, q);
            edid_batch.clear();
        }
    }

    if (!record_batch.empty()) {
        std::string q = "INSERT IGNORE INTO records (source_id, offset, formid, signature, size) VALUES ";
        for (size_t i = 0; i < record_batch.size(); ++i) {
            q += record_batch[i] + (i == record_batch.size() - 1 ? "" : ",");
        }
        execute_query(conn, q);
    }
    if (!edid_batch.empty()) {
        std::string q = "INSERT IGNORE INTO edids (source_id, offset, edid) VALUES ";
        for (size_t i = 0; i < edid_batch.size(); ++i) {
            q += edid_batch[i] + (i == edid_batch.size() - 1 ? "" : ",");
        }
        execute_query(conn, q);
    }

    log("Indexed " + std::to_string(count) + " records and " + std::to_string(assetsCount) + " files from " + path);
}

void processPath(MYSQL* conn, const fs::path& path, const fs::path& root_dir, std::set<std::string>& visited, bool debug) {
    std::string filepath = path.string();
    
    std::string ext = path.extension().string();
    std::string filename = path.filename().string();

    // Calculate virtual path (relative to root_dir)
    std::string virtual_path = fs::relative(path, root_dir).string();
    int64_t fileSize = fs::is_regular_file(path) ? fs::file_size(path) : 0;

    if (ext == ".esm" || ext == ".esp" || ext == ".esl") {
        log("Processing raw plugin " + virtual_path + "...");
        
        // Index as asset
        indexAsset(conn, -1, virtual_path, filepath, "", fileSize);

        std::string source_query = "INSERT IGNORE INTO sources (name, path) VALUES ('" + virtual_path + "', '" + filepath + "')";
        execute_query(conn, source_query);
        
        std::string id_query = "SELECT id FROM sources WHERE path = '" + filepath + "'";
        execute_query(conn, id_query);
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        if (!row) {
            mysql_free_result(res);
            return;
        }
        int source_id = std::stoi(row[0]);
        mysql_free_result(res);

        std::unique_ptr<IReadStream> stream = std::make_unique<FileReadStream>(filepath);
        int assetsCount = 0;
        index_plugin_stream(conn, source_id, stream.get(), virtual_path, assetsCount);
    } 
    else if (ext == ".ba2") {
        log("Processing archive " + filename + "...");
        
        // Index BA2 itself as an asset
        indexAsset(conn, -1, virtual_path, filepath, "", fileSize);

        try {
            std::string source_query = "INSERT IGNORE INTO sources (name, path) VALUES ('" + filename + "', '" + filepath + "')";
            execute_query(conn, source_query);
            
            std::string id_query = "SELECT id FROM sources WHERE path = '" + filepath + "'";
            execute_query(conn, id_query);
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            if (!row) {
                mysql_free_result(res);
                return;
            }
            int source_id = std::stoi(row[0]);
            mysql_free_result(res);

            // Index internal assets
            std::vector<std::string> internal_files = BA2ReadStream::listAllFiles(filepath);
            for (const auto& internal_path : internal_files) {
                // Find size (BA2ReadStream should ideally provide this, but for now we index it)
                indexAsset(conn, source_id, internal_path, filepath, internal_path, 0);
                
                // If internal file is a plugin, index its records
                if (internal_path.ends_with(".esm") || internal_path.ends_with(".esp") || internal_path.ends_with(".esl")) {
                    log("Indexing plugin " + internal_path + " from BA2...");
                    
                    // For the records table, we need a unique source entry for this specific internal plugin
                    std::string p_source_query = "INSERT IGNORE INTO sources (name, path) VALUES ('" + internal_path + "', '" + filepath + " (" + internal_path + ")')";
                    execute_query(conn, p_source_query);
                    
                    std::string p_id_query = "SELECT id FROM sources WHERE path = '" + filepath + " (" + internal_path + ")'";
                    execute_query(conn, p_id_query);
                    MYSQL_RES* pres = mysql_store_result(conn);
                    MYSQL_ROW prow = mysql_fetch_row(pres);
                    if (prow) {
                        int p_source_id = std::stoi(prow[0]);
                        std::unique_ptr<IReadStream> stream = std::make_unique<BA2ReadStream>(filepath, internal_path);
                        int assetsCount = 0;
                        index_plugin_stream(conn, p_source_id, stream.get(), internal_path, assetsCount);
                    }
                    mysql_free_result(pres);
                }
            }
        } catch (const std::exception& e) {
            log("Error processing BA2 " + filename + ": " + e.what(), true);
        }
    } else {
        // Just a generic asset (loose file)
        indexAsset(conn, -1, virtual_path, filepath, "", fileSize);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--debug] [--dry-run] <data_directory_or_file>" << std::endl;
        return 1;
    }

    bool debug = false;
    bool dryRun = false;
    std::string target_path;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--debug") {
            debug = true;
        } else if (arg == "--dry-run") {
            dryRun = true;
        } else {
            target_path = arg;
        }
    }

    if (target_path.empty()) {
        std::cerr << "Error: No target path provided." << std::endl;
        return 1;
    }

    g_dryRun = dryRun;
    DbConfig config = get_db_config();

    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, config.host.c_str(), config.user.c_str(), config.pass.c_str(), config.db.c_str(), 0, nullptr, 0)) {
        std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    log("Connected to database " + config.db + " at " + config.host);

    if (!g_dryRun) {
        execute_query(conn, "SET FOREIGN_KEY_CHECKS = 0");
        execute_query(conn, "TRUNCATE TABLE edids");
        execute_query(conn, "TRUNCATE TABLE records");
        execute_query(conn, "TRUNCATE TABLE assets");
        execute_query(conn, "TRUNCATE TABLE sources");
        execute_query(conn, "SET FOREIGN_KEY_CHECKS = 1");
        log("Database cleared. Starting fresh index...");
    } else {
        log("Dry run enabled: skipping database truncation.");
    }

    std::set<std::string> visited;
    try {
        if (fs::is_regular_file(target_path)) {
            fs::path p = fs::absolute(target_path);
            if (visited.insert(p.string()).second) {
                processPath(conn, p, p.parent_path(), visited, debug);
            }
        } else if (fs::is_directory(target_path)) {
            fs::path root = fs::absolute(target_path);
            for (const auto& entry : fs::recursive_directory_iterator(root)) {
                if (entry.is_regular_file()) {
                    fs::path p = fs::absolute(entry.path());
                    std::string p_str = p.string();
                    
                    if (debug) {
                        bool seen = visited.count(p_str);
                        log("[DEBUG] Iterator yielded: \"" + p_str + "\" (Seen: " + (seen ? "YES" : "NO") + ")");
                    }

                    if (visited.insert(p_str).second) {
                        processPath(conn, p, root, visited, debug);
                    }
                }
            }
        } else {
            log("Error: " + target_path + " is not a valid file or directory.", true);
        }
    } catch (const std::exception& e) {
        log("Error: " + std::string(e.what()), true);
    }

    log("Bulk dump complete.");
    mysql_close(conn);
    return 0;
}
