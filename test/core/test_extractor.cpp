#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "extractor.hpp"
#include "vfs.hpp"
#include "mysql_client.hpp"
#include <filesystem>
#include <fstream>

using namespace starfield;

TEST_CASE("Extractor - Raw Offset Extraction") {
    // Setup: Create a dummy ESM-like file with a known record
    std::string testFile = "test_blob.esm";
    {
        std::ofstream ofs(testFile, std::ios::binary);
        char sig[4] = {'T', 'E', 'S', 'T'};
        ofs.write(sig, 4);
        uint32_t size = 40;
        ofs.write(reinterpret_cast<char*>(&size), 4);
        char padding[16] = {0}; 
        ofs.write(padding, 16); // Total 24 bytes
        
        char data[40] = "This is the record data content!";
        ofs.write(data, 40);
    }

    auto stream = std::make_shared<FileReadStream>(testFile);
    Extractor extractor(stream);

    SUBCASE("Extract valid record at offset 0") {
        auto blob = extractor.extractRecord(0);
        REQUIRE(blob.size() == 64);
        CHECK(blob[0] == 'T');
    }

    SUBCASE("Extract from invalid offset") {
        auto blob = extractor.extractRecord(1000); // Way past end
        CHECK(blob.empty());
    }

    std::filesystem::remove(testFile);
}

TEST_CASE("Extractor - DB Integrated Extraction") {
    // Use the existing starfield_test DB and the golden file
    std::string esmPath = "test/core/golden_test.esm";
    auto stream = std::make_shared<FileReadStream>(esmPath);
    Extractor extractor(stream);
    
    MySQLClient db({"localhost", "root", "root", "starfield_test"});
    REQUIRE(db.connect());

    SUBCASE("Extract by EDID: GoldenQuest") {
        auto results = db.query("SELECT offset FROM edids WHERE edid = 'GoldenQuest' LIMIT 1");
        REQUIRE(!results.empty());
        REQUIRE(!results[0].empty());

        uint64_t offset = std::stoull(results[0][0]);
        auto blob = extractor.extractRecord(offset);
        
        REQUIRE(!blob.empty());
        CHECK(blob.size() >= 24);
    }

    SUBCASE("Extract non-existent EDID") {
        auto results = db.query("SELECT offset FROM edids WHERE edid = 'NON_EXISTENT_EDID' LIMIT 1");
        CHECK(results.empty());
    }
}
