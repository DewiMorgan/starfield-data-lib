#include "asset_extractor.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace starfield::core {

std::optional<std::string> AssetExtractor::findAssetPath(const Record& record) const {
    // Asset paths are typically stored in the MODL tag for many record types
    auto path = record.getString("MODL");
    if (path) return path;
    
    return std::nullopt;
}

bool AssetExtractor::extractAsset(const Record& record, const std::string& outputDir) const {
    auto pathOpt = findAssetPath(record);
    if (!pathOpt) {
        return false;
    }

    std::string assetPath = *pathOpt;
    
    try {
        BA2ReadStream ba2(config.ba2Path, assetPath);
        
        // Create output directory
        std::filesystem::path fullOutPath = std::filesystem::path(outputDir) / assetPath;
        std::filesystem::create_directories(fullOutPath.parent_path());

        std::ofstream outFile(fullOutPath, std::ios::binary);
        if (!outFile) return false;

        std::vector<uint8_t> buffer(4096);
        size_t bytesRead;
        while ((bytesRead = ba2.read(buffer.data(), buffer.size())) > 0) {
            outFile.write(reinterpret_cast<const char*>(buffer.data()), bytesRead);
        }
    } catch (const std::exception& e) {
        std::cerr << "Extraction error: " << e.what() << std::endl;
        return false;
    } catch (...) {
        return false;
    }
    
    return true;
}

} // namespace starfield::core
