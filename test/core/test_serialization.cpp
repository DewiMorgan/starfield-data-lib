#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "record.hpp"
#include "record_writer.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace starfield::core;

// Helper to create a simple binary record for testing
std::vector<uint8_t> createBinaryRecord(const std::string& sig, const std::vector<std::pair<std::string, std::string>>& tlvs) {
    std::vector<uint8_t> blob;
    
    // 1. Record Header (simplified for tests, match the struct in parser.hpp)
    // Signature (4)
    for(char c : sig) blob.push_back(c);
    
    // VCS/Flags (16)
    for(int i=0; i<16; ++i) blob.push_back(0);
    
    // Data Size (4)
    uint32_t dataSize = 0;
    for(const auto& tlv : tlvs) {
        dataSize += (4 + 2 + tlv.second.length());
    }

    // Patch the dataSize at the correct offset (4)
    blob.resize(24);
    uint32_t leSize = dataSize; // Little Endian
    std::memcpy(&blob[4], &leSize, 4);

    // 2. TLVs
    for(const auto& tlv : tlvs) {
        // Tag (4)
        std::string tag = tlv.first;
        while(tag.length() < 4) tag += ' ';
        for(int i=0; i<4; ++i) blob.push_back(tag[i]);

        // Length (2)
        uint16_t len = static_cast<uint16_t>(tlv.second.length());
        uint8_t lenBytes[2];
        std::memcpy(lenBytes, &len, 2);
        blob.push_back(lenBytes[0]);
        blob.push_back(lenBytes[1]);

        // Value
        for(char c : tlv.second) blob.push_back(c);
    }
    
    return blob;
}

TEST_CASE("Serialization - Identity Round-Trip") {
    // Setup a binary record: Signature "WEAP", TLVs: "EDID" -> "GoldenGun", "WDMG" -> "\x00\x00\x80\x3f" (1.0f)
    std::vector<std::pair<std::string, std::string>> data = {
        {"EDID", "GoldenGun"},
        {"WDMG", std::string("\x00\x00\x80\x3f")} 
    };
    std::vector<uint8_t> original = createBinaryRecord("WEAP", data);

    // Parse -> Serialize
    auto rec_opt = Record::parse(original);
    REQUIRE(rec_opt.has_value());
    Record& rec = *rec_opt;
    
    std::vector<uint8_t> serialized = rec.serialize();

    std::cout << "Original size: " << original.size() << ", Serialized size: " << serialized.size() << std::endl;

    // The result should be bit-for-bit identical
    REQUIRE(original.size() == serialized.size());
    for(size_t i=0; i<original.size(); ++i) {
        CHECK(original[i] == serialized[i]);
    }
}

TEST_CASE("Serialization - Mutation") {
    std::vector<std::pair<std::string, std::string>> data = {
        {"EDID", "OldName"}
    };
    std::vector<uint8_t> original = createBinaryRecord("WEAP", data);

    auto rec_opt = Record::parse(original);
    REQUIRE(rec_opt.has_value());
    Record& rec = *rec_opt;

    // Modify the EDID
    rec.setTlvString("EDID", "NewName");

    std::vector<uint8_t> serialized = rec.serialize();
    
    // Parse back to verify
    auto verified_opt = Record::parse(serialized);
    REQUIRE(verified_opt.has_value());
    Record& verified = *verified_opt;
    CHECK(verified.getString("EDID") == "NewName");
    
    // Verify size changed (NewName is longer than OldName)
    CHECK(serialized.size() > original.size());
}

TEST_CASE("Serialization - Structural Change") {
    std::vector<std::pair<std::string, std::string>> data = {
        {"EDID", "TestItem"}
    };
    std::vector<uint8_t> original = createBinaryRecord("WEAP", data);

    auto rec_opt = Record::parse(original);
    REQUIRE(rec_opt.has_value());
    Record& rec = *rec_opt;

    // Add a new TLV
    rec.setTlvString("WVAL", "Valuable");
    
    // Remove the EDID
    rec.removeTlv("EDID");

    std::vector<uint8_t> serialized = rec.serialize();
    
    auto verified_opt = Record::parse(serialized);
    REQUIRE(verified_opt.has_value());
    Record& verified = *verified_opt;
    
    CHECK(verified.getString("WVAL") == "Valuable");
    CHECK(verified.hasTag("EDID") == false);
}
