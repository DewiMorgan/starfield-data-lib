#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/core/parser.hpp"
#include <vector>
#include <cmath>
#include <cstring>

TEST_CASE("Starfield Parser: Basic TLV Types") {
    RecordHeader header;
    header.dataSize = 0; // Set dynamically in tests

    SUBCASE("String field") {
        std::vector<uint8_t> buffer = { 
            'E', 'D', 'I', 'D', 0x05, 0x00, 'H', 'e', 'l', 'l', 'o' 
        };
        header.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.getTlvString("EDID") == "Hello");
    }

    SUBCASE("Int32 field") {
        uint32_t val = 12345;
        std::vector<uint8_t> buffer = { 'W', 'V', 'A', 'L', 0x04, 0x00 };
        uint8_t valBytes[4];
        memcpy(valBytes, &val, 4);
        buffer.insert(buffer.end(), valBytes, valBytes + 4);
        
        header.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.getTlvUint32("WVAL") == 12345);
    }

    SUBCASE("Float field") {
        float val = 12.34f;
        std::vector<uint8_t> buffer = { 'W', 'W', 'E', 'I', 0x04, 0x00 };
        uint8_t valBytes[4];
        memcpy(valBytes, &val, 4);
        buffer.insert(buffer.end(), valBytes, valBytes + 4);
        
        header.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(std::abs(rec.getTlvFloat("WWEI") - 12.34f) < 0.001f);
    }
}

TEST_CASE("Starfield Parser: Mixed and Complex Records") {
    RecordHeader header;

    SUBCASE("Mixed TLVs") {
        // EDID: "Sword", WVAL: 100, WWEI: 2.0
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x05, 0x00, 'S', 'w', 'o', 'r', 'd' };
        uint32_t val = 100;
        uint8_t vB[4]; memcpy(vB, &val, 4);
        buffer.insert(buffer.end(), {'W', 'V', 'A', 'L', 0x04, 0x00});
        buffer.insert(buffer.end(), vB, vB + 4);
        float wei = 2.0f;
        uint8_t wB[4]; memcpy(wB, &wei, 4);
        buffer.insert(buffer.end(), {'W', 'W', 'E', 'I', 0x04, 0x00});
        buffer.insert(buffer.end(), wB, wB + 4);

        header.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.getTlvString("EDID") == "Sword");
        CHECK(rec.getTlvUint32("WVAL") == 100);
        CHECK(std::abs(rec.getTlvFloat("WWEI") - 2.0f) < 0.001f);
    }

    SUBCASE("NPC Record simulation") {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x03, 0x00, 'N', 'P', 'C' };
        uint32_t raceId = 0x12345678;
        uint8_t rB[4]; memcpy(rB, &raceId, 4);
        buffer.insert(buffer.end(), {'R', 'N', 'A', 'M', 0x04, 0x00});
        buffer.insert(buffer.end(), rB, rB + 4);
        uint32_t classId = 0x87654321;
        uint8_t cB[4]; memcpy(cB, &classId, 4);
        buffer.insert(buffer.end(), {'C', 'N', 'A', 'M', 0x04, 0x00});
        buffer.insert(buffer.end(), cB, cB + 4);
        uint32_t combatId = 0xABCDEF01;
        uint8_t coB[4]; memcpy(coB, &combatId, 4);
        buffer.insert(buffer.end(), {'Z', 'N', 'A', 'M', 0x04, 0x00});
        buffer.insert(buffer.end(), coB, coB + 4);

        header.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.getTlvString("EDID") == "NPC");
        CHECK(rec.getTlvFormID("RNAM") == 0x12345678);
        CHECK(rec.getTlvFormID("CNAM") == 0x87654321);
        CHECK(rec.getTlvFormID("ZNAM") == 0xABCDEF01);
    }
}

TEST_CASE("Starfield Parser: Edge Cases & Robustness") {
    RecordHeader header;

    SUBCASE("Empty buffer") {
        std::vector<uint8_t> buffer = {};
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.tlvs.empty());
        CHECK(rec.subRecords.empty());
    }

    SUBCASE("Buffer too small for TLV header") {
        std::vector<uint8_t> buffer = { 'T', 'A', 'G' }; // Only 3 bytes, need 6
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.tlvs.empty());
    }

    SUBCASE("Malformed TLV: Length exceeds remaining buffer") {
        // Tag "TEST", Length 100, but only 4 bytes follow
        std::vector<uint8_t> buffer = { 'T', 'E', 'S', 'T', 0x64, 0x00, 1, 2, 3, 4 };
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        
        CHECK(rec.tlvs.empty());
        REQUIRE(rec.subRecords.size() == 1);
        CHECK(rec.subRecords[0].sig == "TEST");
    }

    SUBCASE("Non-alphanumeric tag") {
        // Tag "T@G!", Length 4, Data [1,2,3,4]
        std::vector<uint8_t> buffer = { 'T', '@', 'G', '!', 0x04, 0x00, 1, 2, 3, 4 };
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        
        CHECK(rec.tlvs.empty());
        REQUIRE(rec.subRecords.size() == 1);
        CHECK(rec.subRecords[0].sig == "T@G!");
    }

    SUBCASE("Null-terminated string") {
        // String "Hello\0World" should be truncated to "Hello"
        std::vector<uint8_t> buffer = { 'S', 'T', 'R', 'I', 0x0A, 0x00, 'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd' };
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        CHECK(rec.getTlvString("STRI") == "Hello");
    }
}

TEST_CASE("StarfieldRecord: Getter Robustness") {
    StarfieldRecord rec;
    
    SUBCASE("Request non-existent tag") {
        CHECK(rec.getTlvString("NONE") == "");
        CHECK(rec.getTlvUint32("NONE") == 0);
        CHECK(rec.getTlvFloat("NONE") == 0.0f);
    }

    SUBCASE("Request field with insufficient data") {
        // Simulate a record with a tag that is too short for a Uint32
        RecordHeader header;
        std::vector<uint8_t> buffer = { 'S', 'H', 'O', 'R', 0x02, 0x00, 0x01, 0x02 };
        header.dataSize = buffer.size();
        StarfieldRecord rec_short = Parser::parseRecord(buffer.data(), buffer.size(), header, 0);
        
        CHECK(rec_short.getTlvUint32("SHOR") == 0);
        CHECK(rec_short.getTlvFloat("SHOR") == 0.0f);
    }
}
