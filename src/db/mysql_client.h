#pragma once

#include <string>
#include <vector>
#include <mysql/mysql.h>

struct DbConfig {
    std::string host;
    std::string user;
    std::string pass;
    std::string db;
};

class MySQLClient {
public:
    MySQLClient(const DbConfig& config, bool dryRun = false);
    ~MySQLClient();

    bool connect();
    void clearDatabase();
    
    void executeQuery(const std::string& query);
    void insertAsset(int source_id, const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size);
    
    void beginRecordBatch();
    void addRecord(int source_id, uint64_t offset, uint32_t formid, const std::string& signature, uint32_t size);
    void addEdid(int source_id, uint64_t offset, const std::string& edid);
    void commitBatch();

    int getOrInsertSource(const std::string& name, const std::string& path);

private:
    DbConfig config_;
    bool dryRun_;
    MYSQL* conn_;

    std::vector<std::string> record_batch_;
    std::vector<std::string> edid_batch_;
};
