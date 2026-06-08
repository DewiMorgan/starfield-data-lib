#pragma once

#include <string>
#include <vector>
#include <optional>
#include <filesystem>
#include "record.hpp"
#include "ba2_stream.hpp"

namespace starfield::core {

class AssetExtractor {
public:
    struct Config {
        std::string ba2Path;
    };

    explicit AssetExtractor(Config config) : config(std::move(config)) {}

    // Extracts an asset associated with the given record
    bool extractAsset(const Record& record, const std::string& outputDir) const;

    // Helper to find the asset path in a record (usually MODL tag)
    std::optional<std::string> findAssetPath(const Record& record) const;

private:
    Config config;
};

} // namespace starfield::core
