#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <memory>

#include "db/mysql_client.hpp"
#include "core/indexer.hpp"
#include "core/parser.hpp"
#include "core/schema.hpp"

namespace fs = std::filesystem;

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

bool g_Debug = false;
bool g_HexOnly = false;
void debugLog(const std::string& msg) {
    if (g_Debug) {
        std::cout << "[DEBUG] [" << getTimestamp() << "] " << msg << std::endl;
    }
}

void printHexDump(IReadStream* stream, size_t bytes) {
    if (!g_Debug && !g_HexOnly) return;
    uint64_t pos = stream->tell();
    std::vector<uint8_t> buffer(bytes);
    size_t read = stream->read(buffer.data(), bytes);
    stream->seek(pos);

    std::cout << "[DEBUG] Hex dump (first " << read << " bytes):" << std::endl;
    for (size_t i = 0; i < read; i += 16) {
        std::cout << std::setw(8) << std::setfill('0') << std::hex << i << ": ";
        for (size_t j = 0; j < 16 && (i + j) < read; ++j) {
            std::cout << std::setw(2) << std::setfill('0') << (int)buffer[i + j] << " ";
        }
        std::cout << std::dec << std::endl;
    }
}

class BulkDumpListener : public IIndexListener {
public:
    BulkDumpListener(MySQLClient* db = nullptr) : db_(db) {}

    void onSourceRegistered(const std::string& name, const std::string& path) override {
        if (!db_) return;
        current_source_id_ = db_->getOrInsertSource(name, path);
    }

    void onAssetFound(const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) override {
        if (!db_) return;
        db_->insertAsset(current_source_id_ == -1 ? -1 : current_source_id_, virtual_path, literal_path, internal_path, size);
    }

    void onPluginFound(int, const std::string& virtual_path, IReadStream* stream) override {
        if (g_HexOnly) {
            debugLog("Hex-only mode: dumping header for " + virtual_path);
            printHexDump(stream, 64);
            return;
        }

        if (!db_) return;

        int records_count = 0;
        uint64_t current_offset = 0;

        debugLog("Processing plugin: " + virtual_path);
        printHexDump(stream, 64);

        db_->beginRecordBatch();
        
        // DO NOT treat the "ESM file header" as a special-case constant size (28 bytes).
	// It's just a variable-size record like any other, and we handle it as such.

        while (true) {
            RecordHeader header;
            size_t readBytes = stream->read(&header, sizeof(RecordHeader));
            if (readBytes < sizeof(RecordHeader)) break;

            if (header.dataSize > 10 * 1024 * 1024) {
                std::string errorMsg = "Unrecoverable error in " + virtual_path + 
                                      " at offset " + std::to_string(current_offset) + 
                                      ": Record size " + std::to_string(header.dataSize) + " is impossible.";
                log(errorMsg, true);
                debugLog("Read " + std::to_string(records_count) + " records before failure.");
                break; 
            }

            std::string sig(header.sig, 4);
            if (g_RecordSchemas.find(sig) == g_RecordSchemas.end()) {
                debugLog("Skipping unknown record signature [" + sig + "] at offset " + std::to_string(current_offset));
                current_offset += sizeof(RecordHeader) + header.dataSize;
                stream->seek(current_offset);
                continue;
            }

            debugLog("Found valid record [" + sig + "] at offset " + std::to_string(current_offset) + " (size: " + std::to_string(header.dataSize) + ")");

            static std::vector<uint8_t> record_buffer;
            if (record_buffer.size() < header.dataSize) {
                debugLog("Resizing record buffer to " + std::to_string(header.dataSize));
                record_buffer.resize(header.dataSize);
            }

            if (stream->read(record_buffer.data(), header.dataSize) < header.dataSize) {
                log("Unexpected EOF while reading record data in " + virtual_path, true);
                break;
            }

            StarfieldRecord record = Parser::parseRecord(record_buffer.data(), header.dataSize, header, current_offset);
            std::string edid = record.getTlvString("EDID");
            
            db_->addRecord(current_source_id_, current_offset, header.formId, sig, header.dataSize);
            if (!edid.empty()) {
                debugLog("Indexed EDID: " + edid + " at offset " + std::to_string(current_offset));
                db_->addEdid(current_source_id_, current_offset, edid);
            }

            records_count++;
            current_offset += sizeof(RecordHeader) + header.dataSize;
            
            if (records_count % 1000 == 0) {
                debugLog("Committing batch at " + std::to_string(records_count) + " records...");
                db_->commitBatch();
            }
        }
        db_->commitBatch();
        
        log("Indexed " + std::to_string(records_count) + " records from " + virtual_path);
    }

private:
    MySQLClient* db_;
    int current_source_id_ = -1;
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--dry-run] [--debug] [--hex-only] <data_directory_or_file>" << std::endl;
        return 1;
    }

    bool dryRun = false;
    std::string target_path;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--dry-run") dryRun = true;
        else if (arg == "--debug") g_Debug = true;
        else if (arg == "--hex-only") g_HexOnly = true;
        else target_path = arg;
    }

    if (g_HexOnly) {
        log("Hex-only mode enabled. Skipping database connection.");
        BulkDumpListener listener(nullptr);
        Indexer indexer(&listener);
        try {
            if (fs::is_regular_file(target_path)) {
                fs::path p = fs::absolute(target_path);
                indexer.processPath(p, p.parent_path());
            } else if (fs::is_directory(target_path)) {
                indexer.processDirectory(fs::absolute(target_path));
            } else {
                log("Error: " + target_path + " is not a valid file or directory.", true);
                return 1;
            }
        } catch (const std::exception& e) {
            log("Error: " + std::string(e.what()), true);
            return 1;
        }
        log("Hex-only scan complete.");
        return 0;
    }

    DbConfig config = MySQLClient::loadConfig();
    MySQLClient db(config, dryRun);
    if (!db.connect()) {
        log("Failed to connect to database.", true);
        return 1;
    }

    log("Connected to database " + config.db + " at " + config.host);

    if (!dryRun) {
        db.clearDatabase();
        log("Database cleared. Starting fresh index...");
    } else {
        log("Dry run enabled: skipping database truncation.");
    }

    BulkDumpListener listener(&db);
    Indexer indexer(&listener);

    try {
        if (fs::is_regular_file(target_path)) {
            fs::path p = fs::absolute(target_path);
            indexer.processPath(p, p.parent_path());
        } else if (fs::is_directory(target_path)) {
            indexer.processDirectory(fs::absolute(target_path));
        } else {
            log("Error: " + target_path + " is not a valid file or directory.", true);
            return 1;
        }
    } catch (const std::exception& e) {
        log("Error: " + std::string(e.what()), true);
        return 1;
    }

    log("Bulk dump complete.");
    return 0;
}
