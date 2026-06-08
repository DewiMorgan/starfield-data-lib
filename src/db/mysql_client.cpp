#include "mysql_client.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>

DbConfig MySQLClient::loadConfig() {
    DbConfig config = {"localhost", "root", "root", "starfield", "starfield_test"};
    
    std::ifstream file("db.conf");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value;
                if (std::getline(is_line, value)) {
                    if (key == "host") config.host = value;
                    else if (key == "user") config.user = value;
                    else if (key == "pass") config.pass = value;
                    else if (key == "db") config.db = value;
                    else if (key == "test_db") config.test_db = value;
                }
            }
        }
    } else {
        std::cerr << "[Config] Warning: Could not open db.conf, using defaults." << std::endl;
    }

    if (getenv("USE_TEST_DB")) {
        config.db = config.test_db;
    }
    
    const char* env_host = getenv("MYSQL_HOST");
    if (env_host) config.host = env_host;
    const char* env_user = getenv("MYSQL_USER");
    if (env_user) config.user = env_user;
    const char* env_pass = getenv("MYSQL_PASS");
    if (env_pass) config.pass = env_pass;
    const char* env_db = getenv("MYSQL_DB");
    if (env_db) config.db = env_db;
    
    return config;
}

MySQLClient::MySQLClient(const DbConfig& config, bool dryRun) 
    : config_(config), dryRun_(dryRun), conn_(nullptr) {}

MySQLClient::~MySQLClient() {
    if (conn_) mysql_close(conn_);
}

bool MySQLClient::connect() {
    conn_ = mysql_init(nullptr);
    if (!mysql_real_connect(conn_, config_.host.c_str(), config_.user.c_str(), config_.pass.c_str(), config_.db.c_str(), 0, nullptr, 0)) {
        return false;
    }
    return true;
}

void MySQLClient::executeQuery(const std::string& query) {
    if (dryRun_) {
        std::cout << "[Dry Run] Skipping query: " << query << std::endl;
        return;
    }
    if (mysql_query(conn_, query.c_str())) {
        std::cerr << "MySQL Error: " << mysql_error(conn_) << "\nQuery: " << query << std::endl;
    }
}

std::vector<std::vector<std::string>> MySQLClient::query(const std::string& query) {
    if (dryRun_) return {};
    if (mysql_query(conn_, query.c_str())) {
        std::cerr << "MySQL Error: " << mysql_error(conn_) << "\nQuery: " << query << std::endl;
        return {};
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    if (!res) return {};

    std::vector<std::vector<std::string>> results;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::vector<std::string> row_data;
        unsigned int num_fields = mysql_num_fields(res);
        for (unsigned int i = 0; i < num_fields; ++i) {
            row_data.push_back(row[i] ? row[i] : "");
        }
        results.push_back(row_data);
    }
    mysql_free_result(res);
    return results;
}

void MySQLClient::clearDatabase() {
    executeQuery("SET FOREIGN_KEY_CHECKS = 0");
    executeQuery("TRUNCATE TABLE edids");
    executeQuery("TRUNCATE TABLE records");
    executeQuery("TRUNCATE TABLE assets");
    executeQuery("TRUNCATE TABLE sources");
    executeQuery("SET FOREIGN_KEY_CHECKS = 1");
}

void MySQLClient::insertAsset(int source_id, const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) {
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
    executeQuery(q);
}

int MySQLClient::getOrInsertSource(const std::string& name, const std::string& path) {
    auto esc = [](std::string s) {
        size_t pos = 0;
        while ((pos = s.find("'", pos)) != std::string::npos) {
            s.replace(pos, 1, "''");
            pos += 2;
        }
        return s;
    };

    std::string insert_q = "INSERT IGNORE INTO sources (name, path) VALUES ('" + esc(name) + "', '" + esc(path) + "')";
    executeQuery(insert_q);
    
    std::string select_q = "SELECT id FROM sources WHERE path = '" + esc(path) + "'";
    executeQuery(select_q);
    
    MYSQL_RES* res = mysql_store_result(conn_);
    if (!res) return -1;
    
    MYSQL_ROW row = mysql_fetch_row(res);
    int id = row ? std::stoi(row[0]) : -1;
    mysql_free_result(res);
    return id;
}

void MySQLClient::beginRecordBatch() {
    record_batch_.clear();
    edid_batch_.clear();
}

void MySQLClient::addRecord(int source_id, uint64_t offset, uint32_t formid, const std::string& signature, uint32_t size) {
    char escaped_sig[10]; 
    mysql_real_escape_string(conn_, escaped_sig, signature.c_str(), signature.size());
    
    std::string val = "(" + std::to_string(source_id) + "," + 
                     std::to_string(offset) + "," + 
                     std::to_string(formid) + ",'" + 
                     std::string(escaped_sig) + "'," + 
                     std::to_string(size) + ")";
    record_batch_.push_back(val);
}

void MySQLClient::addEdid(int source_id, uint64_t offset, const std::string& edid) {
    std::string esc_edid = edid;
    size_t pos = 0;
    while ((pos = esc_edid.find("'", pos)) != std::string::npos) {
        esc_edid.replace(pos, 1, "''");
        pos += 2;
    }
    std::string val = "(" + std::to_string(source_id) + "," + 
                     std::to_string(offset) + ",'" + 
                     esc_edid + "')";
    edid_batch_.push_back(val);
}

void MySQLClient::commitBatch() {
    if (!record_batch_.empty()) {
        std::string q = "INSERT IGNORE INTO records (source_id, offset, formid, signature, size) VALUES ";
        for (size_t i = 0; i < record_batch_.size(); ++i) {
            q += record_batch_[i] + (i == record_batch_.size() - 1 ? "" : ",");
        }
        executeQuery(q);
        record_batch_.clear();
    }
    if (!edid_batch_.empty()) {
        std::string q = "INSERT IGNORE INTO edids (source_id, offset, edid) VALUES ";
        for (size_t i = 0; i < edid_batch_.size(); ++i) {
            q += edid_batch_[i] + (i == edid_batch_.size() - 1 ? "" : ",");
        }
        executeQuery(q);
        edid_batch_.clear();
    }
}
