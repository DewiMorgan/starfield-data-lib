#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <set>
#include "vfs.h"

class IIndexListener {
public:
    virtual ~IIndexListener() = default;
    virtual void onAssetFound(const std::string& virtual_path, const std::string& literal_path, const std::string& internal_path, int64_t size) = 0;
    virtual void onPluginFound(int source_id, const std::string& virtual_path, IReadStream* stream) = 0;
    virtual void onSourceRegistered(const std::string& name, const std::string& path) = 0;
};

class Indexer {
public:
    Indexer(IIndexListener* listener);
    
    void processPath(const std::filesystem::path& target_path, const std::filesystem::path& root_dir);
    void processDirectory(const std::filesystem::path& root_dir);

private:
    void handleFile(const std::filesystem::path& path, const std::filesystem::path& root_dir);
    void handleBA2(const std::filesystem::path& path, const std::filesystem::path& root_dir);
    
    IIndexListener* listener_;
    std::set<std::string> visited_;
};
