#pragma once

#include <string>
#include <vector>
#include <cstdint>

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool connect() = 0;
    virtual void clearDatabase() = 0;
    
    virtual void executeQuery(const std::string& query) = 0;
    virtual std::vector<std::vector<std::string>> query(const std::string& query) = 0;
    virtual void insertAsset(int source_id, const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) = 0;
    
    virtual void beginRecordBatch() = 0;
    virtual void addRecord(int source_id, uint64_t offset, uint32_t formid, const std::string& signature, uint32_t size) = 0;
    virtual void addEdid(int source_id, uint64_t offset, const std::string& edid) = 0;
    virtual void commitBatch() = 0;

    virtual int getOrInsertSource(const std::string& name, const std::string& path) = 0;
};
