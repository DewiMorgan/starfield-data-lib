#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "core/asset_extractor.hpp"
#include "core/record.hpp"
#include "core/ba2_stream.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Helper to create a minimal BA2 file for testing
void createTestBA2(const std::string& path, const std::string& fileName, const std::string& content) {
    std::ofstream file(path, std::ios::binary);
    
    // Extremely simplified BA2-like header for our test
    // In a real scenario, we'd use the actual BA2 format
    // But since BA2ReadStream is what we're testing, we must match its expectations.
    // Let's just write the files in a way that our current BA2ReadStream can handle,
    // or better yet, use a real BA2 if available.
    
    // Since we have a real BA2 in vendor, let's use that for integration and 
    // a mock/synthetic one for unit tests.
}

TEST_CASE("Asset Extraction - Path Lookup") {
    starfield::core::Record rec;
    rec.setTlvString("MODL", "Items\\Weapon\\Sword.nif");
    
    starfield::core::AssetExtractor extractor({"test.ba2"});
    auto path = extractor.findAssetPath(rec);
    
    REQUIRE(path.has_value());
    CHECK(*path == "Items\\Weapon\\Sword.nif");
}

TEST_CASE("Asset Extraction - No Path") {
    starfield::core::Record rec;
    rec.setTlvString("EDID", "MyWeapon");
    
    starfield::core::AssetExtractor extractor({"test.ba2"});
    auto path = extractor.findAssetPath(rec);
    
    CHECK(!path.has_value());
}

// Note: Full BA2 integration test requires a valid BA2 file.
// We will verify the logic against the vendor samples in the integration phase.
