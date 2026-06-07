#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/core/ba2_stream.h"
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstring>

struct BA2Header {
    char magic[4];
    uint32_t version;
    char type[4];
    uint32_t numFiles;
    uint64_t nameTableOffset;
    uint32_t unknown[3];
};

struct BA2FileEntry {
    uint32_t nameHash;
    char extension[4];
    uint32_t dirHash;
    uint32_t flags;
    uint64_t offset;
    uint32_t compressedSize;
    uint32_t realSize;
    uint32_t align;
};

void create_mock_ba2(const std::string& path, const std::string& filename, const std::vector<uint8_t>& content) {
    std::ofstream ofs(path, std::ios::binary);

    BA2Header header;
    std::memcpy(header.magic, "BA2 ", 4);
    header.version = 1;
    std::memcpy(header.type, "TYPE", 4);
    header.numFiles = 1;
    
    // Calculate offsets
    // Header + 1 Entry + Content = NameTableOffset
    header.nameTableOffset = sizeof(BA2Header) + sizeof(BA2FileEntry) + content.size();
    std::memset(header.unknown, 0, sizeof(header.unknown));

    BA2FileEntry entry;
    entry.nameHash = 0; // Not used by our current BA2ReadStream
    std::memcpy(entry.extension, ".esm", 4);
    entry.dirHash = 0;
    entry.flags = 0;
    entry.offset = sizeof(BA2Header) + sizeof(BA2FileEntry);
    entry.compressedSize = content.size(); // Stored, not compressed
    entry.realSize = content.size();
    entry.align = 0;

    ofs.write(reinterpret_cast<char*>(&header), sizeof(header));
    ofs.write(reinterpret_cast<char*>(&entry), sizeof(entry));
    ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
    
    // Name Table
    uint16_t len = static_cast<uint16_t>(filename.size());
    ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
    ofs.write(filename.data(), len);
}

TEST_CASE("BA2ReadStream Basic Extraction") {
    std::string path = "test_mock.ba2";
    std::string filename = "test.esm";
    std::vector<uint8_t> content = {0xDE, 0xAD, 0xBE, 0xEF};
    
    create_mock_ba2(path, filename, content);

    {
        BA2ReadStream stream(path, filename);
        CHECK(stream.size() == 4);
        
        uint8_t buffer[4];
        size_t read = stream.read(buffer, 4);
        CHECK(read == 4);
        CHECK(buffer[0] == 0xDE);
        CHECK(buffer[3] == 0xEF);
    }

    std::filesystem::remove(path);
}

TEST_CASE("BA2ReadStream Listing") {
    std::string path = "test_list.ba2";
    std::string filename = "plugin.esm";
    std::vector<uint8_t> content = {0x00};
    
    create_mock_ba2(path, filename, content);

    auto allFiles = BA2ReadStream::listAllFiles(path);
    REQUIRE(allFiles.size() == 1);
    CHECK(allFiles[0] == filename);

    auto plugins = BA2ReadStream::listPlugins(path);
    REQUIRE(plugins.size() == 1);
    CHECK(plugins[0] == filename);

    std::filesystem::remove(path);
}

TEST_CASE("BA2ReadStream Errors") {
    std::string path = "test_err.ba2";
    std::string filename = "exists.esm";
    std::vector<uint8_t> content = {0x00};
    create_mock_ba2(path, filename, content);

    CHECK_THROWS_AS(BA2ReadStream(path, "nonexistent.esm"), std::runtime_error);
    CHECK_THROWS_AS(BA2ReadStream("nonexistent.ba2", filename), std::runtime_error);

    std::filesystem::remove(path);
}
