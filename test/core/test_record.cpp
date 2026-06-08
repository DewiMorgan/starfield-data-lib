#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "record.hpp"
#include <vector>
#include <cstring>

using namespace starfield::core;

// Helper to create a dummy record blob
std::vector<uint8_t> createDummyRecord() {
    std::vector<uint8_t> data(100, 0); // Allocate enough space for the dummy record
    
    // Signature: "QUST"
    std::memcpy(data.data(), "QUST", 4);
    
    // Data Size: 40 bytes
    uint32_t size = 40;
    std::memcpy(data.data() + 4, &size, 4);

    // TLV 1: "EDID" -> "TestQuest" (9 bytes)
    std::memcpy(data.data() + 24, "EDID", 4);
    uint16_t len1 = 9;
    std::memcpy(data.data() + 28, &len1, 2);
    std::memcpy(data.data() + 30, "TestQuest", 9);

    // TLV 2: "WDMG" -> 42.5f (4 bytes)
    std::memcpy(data.data() + 39, "WDMG", 4);
    uint16_t len2 = 4;
    std::memcpy(data.data() + 43, &len2, 2);
    float dmg = 42.5f;
    std::memcpy(data.data() + 45, &dmg, 4);

    // TLV 3: "VAL1" -> 100 (4 bytes)
    std::memcpy(data.data() + 49, "VAL1", 4);
    uint16_t len3 = 4;
    std::memcpy(data.data() + 53, &len3, 2);
    int32_t val = 100;
    std::memcpy(data.data() + 55, &val, 4);

    return data;
}

TEST_CASE("Record Object Decomposition") {
    auto blob = createDummyRecord();
    auto record = Record::parse(blob);

    REQUIRE(record.has_value());
    
    SUBCASE("Header Verification") {
        CHECK(record->getSignature() == "QUST");
        CHECK(record->getDataSize() == 40);
    }

    SUBCASE("TLV Retrieval") {
        CHECK(record->hasTag("EDID"));
        CHECK(record->getString("EDID") == "TestQuest");

        CHECK(record->hasTag("WDMG"));
        CHECK(record->getFloat("WDMG") == 42.5f);

        CHECK(record->hasTag("VAL1"));
        CHECK(record->getInt32("VAL1") == 100);
    }

    SUBCASE("Missing Tags") {
        CHECK_FALSE(record->hasTag("NONE"));
        CHECK(record->getString("NONE") == std::nullopt);
    }

    SUBCASE("Traversal") {
        const auto& tlvs = record->getTlvs();
        CHECK(tlvs.size() == 3);
        
        bool foundEdid = false;
        for (const auto& entry : tlvs) {
            if (entry.tag == "EDID") {
                CHECK(entry.data.size() == 9);
                foundEdid = true;
            }
        }
        CHECK(foundEdid);
    }
}

TEST_CASE("Record Edge Cases") {
    SUBCASE("Too Small Blob") {
        std::vector<uint8_t> tiny = {0, 1, 2};
        auto record = Record::parse(tiny);
        CHECK_FALSE(record.has_value());
    }

    SUBCASE("Empty Record (Header Only)") {
        std::vector<uint8_t> headerOnly(24, 0);
        std::memcpy(headerOnly.data(), "TEST", 4);
        auto record = Record::parse(headerOnly);
        REQUIRE(record.has_value());
        CHECK(record->getTlvs().empty());
    }
}
