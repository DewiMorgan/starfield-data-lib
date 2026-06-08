#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>

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

class BulkDumpListener : public IIndexListener {
public:
    BulkDumpListener(MySQLClient* db) : db_(db) {}

    void onSourceRegistered(const std::string& name, const std::string& path) override {
        current_source_id_ = db_->getOrInsertSource(name, path);
    }

    void onAssetFound(const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) override {
        db_->insertAsset(current_source_id_ == -1 ? -1 : current_source_id_, virtual_path, literal_path, internal_path, size);
    }

    void onPluginFound(int, const std::string& virtual_path, IReadStream* stream) override {
        int records_count = 0;
        int assets_count = 0;
        
        db_->beginRecordBatch();
        uint64_t current_offset = 0;
        
        while (true) {
            RecordHeader header;
            size_t readBytes = stream->read(&header, sizeof(RecordHeader));
            if (readBytes < sizeof(RecordHeader)) break;

            std::string sig(header.sig, 4);
            if (g_RecordSchemas.find(sig) == g_RecordSchemas.end()) break;

            std::vector<uint8_t> data(header.dataSize);
            if (stream->read(data.data(), header.dataSize) < header.dataSize) break;

            db_->addRecord(current_source_id_, current_offset, header.formId, sig, header.dataSize);

            StarfieldRecord record = Parser::parseRecord(data.data(), data.size(), header, current_offset);
            std::string edid = record.getTlvString("EDID");
            if (!edid.empty()) {
                db_->addEdid(current_source_id_, current_offset, edid);
            }

            records_count++;
            current_offset += sizeof(RecordHeader) + header.dataSize;
            
            // Commit in chunks to prevent massive queries
            if (records_count % 1000 == 0) db_->commitBatch();
        }
        db_->commitBatch();
        
        log("Indexed " + std::to_string(records_count) + " records and 1 files from " + virtual_path);
    }

private:
    MySQLClient* db_;
    int current_source_id_ = -1;
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--dry-run] <data_directory_or_file>" << std::endl;
        return 1;
    }

    bool dryRun = false;
    std::string target_path;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--dry-run") dryRun = true;
        else target_path = arg;
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
