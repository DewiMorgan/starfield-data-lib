#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "esm_writer.hpp"
#include "record.hpp"
#include "parser.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace starfield::core;
namespace fs = std::filesystem;

// Helper to read a file into a buffer
std::vector<uint8_t> readFile(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    if (!ifs) return {};
    std::streamsize size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(size);
    ifs.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

TEST_CASE("ESM Packing - Bit-Identical Round Trip") {
    std::string sourcePath = "test/core/golden_test.esm";
    std::string targetPath = "test/core/packed_test.esm";

    if (!fs::exists(sourcePath)) {
        MESSAGE("Source golden file not found, skipping test");
        return;
    }

    // 1. Read the original file
    std::vector<uint8_t> originalBytes = readFile(sourcePath);
    REQUIRE(!originalBytes.empty());

    // 2. Parse all records from the original file
    // The file starts with a 4-byte header ("TES4")
    size_t currentPos = 4;
    std::vector<std::shared_ptr<Record>> parsedRecords;

    while (currentPos + sizeof(RecordHeader) <= originalBytes.size()) {
        // Extract the RecordHeader to find the data size
        RecordHeader header;
        std::memcpy(&header, &originalBytes[currentPos], sizeof(RecordHeader));
        
        uint32_t recordTotalSize = sizeof(RecordHeader) + header.dataSize;
        if (currentPos + recordTotalSize > originalBytes.size()) {
            break; // Truncated record
        }

        // Create a blob of [Header + Data] starting from currentPos
        std::vector<uint8_t> recordBlob(
            originalBytes.begin() + currentPos, 
            originalBytes.begin() + currentPos + recordTotalSize
        );

        auto recordOpt = Record::parse(recordBlob);
        if (recordOpt) {
            parsedRecords.push_back(std::make_shared<Record>(*recordOpt));
        } else {
            MESSAGE("Failed to parse record at offset " << currentPos);
        }

        currentPos += recordTotalSize;
    }

    REQUIRE(parsedRecords.size() > 0);

    // 3. Pack the records back into a new file
    ESMWriter writer;
    bool success = writer.write(targetPath, parsedRecords);
    REQUIRE(success == true);

    // 4. Read the packed file
    std::vector<uint8_t> packedBytes = readFile(targetPath);
    REQUIRE(!packedBytes.empty());

    // 5. Bit-for-bit comparison
    REQUIRE(originalBytes.size() == packedBytes.size());
    
    bool identical = true;
    for (size_t i = 0; i < originalBytes.size(); ++i) {
        if (originalBytes[i] != packedBytes[i]) {
            identical = false;
            break;
        }
    }

    CHECK(identical == true);
}
