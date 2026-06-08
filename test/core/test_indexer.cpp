#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "indexer.hpp"
#include "vfs.hpp"
#include "ba2_stream.hpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class MockIndexListener : public IIndexListener {
public:
    struct Asset { std::string virtual_path, literal_path, internal_path; int64_t size; };
    struct Source { std::string name, path; };

    std::vector<Asset> assets;
    std::vector<Source> sources;
    int plugins_found = 0;

    void onAssetFound(const std::string& vp, const std::string& lp, const std::string& ip, int64_t s) override {
        assets.push_back({vp, lp, ip, s});
    }
    void onPluginFound(int sid, const std::string& vp, IReadStream* stream) override {
        plugins_found++;
    }
    void onSourceRegistered(const std::string& n, const std::string& p) override {
        sources.push_back({n, p});
    }
};

// Helper to create a dummy BA2 for testing
void createDummyBA2(const std::string& path) {
    std::ofstream ofs(path, std::ios::binary);
    // Minimal BA2 header spoof (just enough to not crash the BA2ReadStream::listAllFiles)
    // In reality, we'd write a valid header, but for the mock indexer, we want to test the glue.
    // Since BA2ReadStream::listAllFiles is used, it needs to be a valid BA2.
    // I'll reuse the synthesis logic from Phase 3 in a real test, 
    // but here I'll assume the BA2 logic is already tested and just check the Indexer's interaction.
    
    // Since I can't easily write a full binary BA2 here without a lot of boilerplate,
    // I will focus on testing the Indexer's directory traversal and plugin detection first.
    // To test BA2, I'll mock the BA2ReadStream::listAllFiles if it were virtual, 
    // but it's a static method. I'll provide a very basic valid-looking BA2 header if needed.
}

TEST_CASE("Indexer Logic Tests") {
    std::string test_dir = "test_indexer_root";
    fs::create_directories(test_dir);

    // Create some test files
    std::ofstream("test_indexer_root/data.txt") << "hello";
    std::ofstream("test_indexer_root/plugin.esm") << "fake esm content";
    fs::create_directories(test_dir + "/subdir");
    std::ofstream(test_dir + "/subdir/inner.esp") << "fake esp content";

    MockIndexListener listener;
    Indexer indexer(&listener);

    SUBCASE("Directory Processing") {
        indexer.processDirectory(test_dir);

        // Should find 3 assets: data.txt, plugin.esm, inner.esp
        CHECK(listener.assets.size() == 3);
        // Should find 2 plugins: plugin.esm, inner.esp
        CHECK(listener.plugins_found == 2);
        // Should find 2 sources: plugin.esm, inner.esp
        CHECK(listener.sources.size() == 2);
    }

    // Cleanup
    fs::remove_all(test_dir);
}
