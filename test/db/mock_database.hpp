#pragma once

#include "idatabase.hpp"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

struct MockAsset {
    int id;
    int source_id;
    std::string virtual_path;
    std::string literal_path;
    std::string internal_path;
    int64_t size;
};

struct MockSource {
    int id;
    std::string name;
    std::string path;
};

struct MockRecord {
    int source_id;
    uint64_t offset;
    uint32_t formid;
    std::string signature;
    uint32_t size;
};

struct MockEdid {
    int source_id;
    uint64_t offset;
    std::string edid;
};

class MockDatabase : public IDatabase {
public:
    bool connect() override { return true; }
    
    void clearDatabase() override {
        sources.clear();
        assets.clear();
        records.clear();
        edids.clear();
        next_source_id = 1;
        next_asset_id = 1;
    }

    void executeQuery(const std::string& query) override {
        // Mock barely uses this, just ignore or log for debug
    }

    std::vector<std::vector<std::string>> query(const std::string& query) override {
        // Very basic SQL simulation for the specific counts used in tests
        if (query.find("SELECT count(*) FROM assets WHERE virtual_path =") != std::string::npos) {
            size_t pos = query.find("'");
            size_t end_pos = query.find("'", pos + 1);
            std::string path = query.substr(pos + 1, end_pos - pos - 1);
            
            int count = 0;
            for (const auto& a : assets) if (a.virtual_path == path) count++;
            return {{std::to_string(count)}};
        }
        if (query.find("SELECT count(*) FROM records") != std::string::npos) {
            return {{std::to_string(records.size())}};
        }
        if (query.find("SELECT count(*) FROM edids") != std::string::npos) {
            return {{std::to_string(edids.size())}};
        }
        return {};
    }

    void insertAsset(int source_id, const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) override {
        assets.push_back({next_asset_id++, source_id, virtual_path, literal_path, internal_path, size});
    }

    void beginRecordBatch() override {
        pending_records.clear();
        pending_edids.clear();
    }

    void addRecord(int source_id, uint64_t offset, uint32_t formid, const std::string& signature, uint32_t size) override {
        pending_records.push_back({source_id, offset, formid, signature, size});
    }

    void addEdid(int source_id, uint64_t offset, const std::string& edid) override {
        pending_edids.push_back({source_id, offset, edid});
    }

    void commitBatch() override {
        for (const auto& r : pending_records) records.push_back(r);
        for (const auto& e : pending_edids) edids.push_back(e);
        pending_records.clear();
        pending_edids.clear();
    }

    int getOrInsertSource(const std::string& name, const std::string& path) override {
        for (const auto& s : sources) {
            if (s.path == path) return s.id;
        }
        int id = next_source_id++;
        sources.push_back({id, name, path});
        return id;
    }

private:
    int next_source_id = 1;
    int next_asset_id = 1;
    std::vector<MockSource> sources;
    std::vector<MockAsset> assets;
    std::vector<MockRecord> records;
    std::vector<MockEdid> edids;

    std::vector<MockRecord> pending_records;
    std::vector<MockEdid> pending_edids;
};
