#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include "../src/parser.h"

void test_parse_string() {
    std::cout << "Testing String field..." << std::endl;
    std::vector<uint8_t> buffer = { 
        'E', 'D', 'I', 'D', 0x05, 0x00, 'H', 'e', 'l', 'l', 'o' 
    };
    RecordHeader header;
    header.dataSize = buffer.size();
    
    StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header);
    assert(rec.getTlvString("EDID") == "Hello");
    std::cout << "Pass!" << std::endl;
}

void test_parse_int() {
    std::cout << "Testing Int32 field..." << std::endl;
    uint32_t val = 12345;
    std::vector<uint8_t> buffer = { 
        'W', 'V', 'A', 'L', 0x04, 0x00 
    };
    uint8_t valBytes[4];
    memcpy(valBytes, &val, 4);
    buffer.insert(buffer.end(), valBytes, valBytes + 4);

    RecordHeader header;
    header.dataSize = buffer.size();
    
    StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header);
    assert(rec.getTlvUint32("WVAL") == 12345);
    std::cout << "Pass!" << std::endl;
}

void test_parse_float() {
    std::cout << "Testing Float field..." << std::endl;
    float val = 12.34f;
    std::vector<uint8_t> buffer = { 
        'W', 'W', 'E', 'I', 0x04, 0x00 
    };
    uint8_t valBytes[4];
    memcpy(valBytes, &val, 4);
    buffer.insert(buffer.end(), valBytes, valBytes + 4);

    RecordHeader header;
    header.dataSize = buffer.size();
    
    StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header);
    assert(std::abs(rec.getTlvFloat("WWEI") - 12.34f) < 0.001f);
    std::cout << "Pass!" << std::endl;
}

void test_mixed_record() {
    std::cout << "Testing Mixed record..." << std::endl;
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

    RecordHeader header;
    header.dataSize = buffer.size();
    
    StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header);
    assert(rec.getTlvString("EDID") == "Sword");
    assert(rec.getTlvUint32("WVAL") == 100);
    assert(std::abs(rec.getTlvFloat("WWEI") - 2.0f) < 0.001f);
    std::cout << "Pass!" << std::endl;
}

void test_expanded_records() {
    std::cout << "Testing Expanded Records..." << std::endl;

    // NPC_ Test
    {
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

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "NPC");
        assert(rec.getTlvFormID("RNAM") == 0x12345678);
        assert(rec.getTlvFormID("CNAM") == 0x87654321);
        assert(rec.getTlvFormID("ZNAM") == 0xABCDEF01);
    }

    // ARMO Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'A', 'R', 'M', 'O' };
        uint32_t bidsId = 0x87654321;
        uint8_t bB[4]; memcpy(bB, &bidsId, 4);
        buffer.insert(buffer.end(), {'B', 'I', 'D', 'S', 0x04, 0x00});
        buffer.insert(buffer.end(), bB, bB + 4);
        
        uint32_t snddId = 0xDEADBEEF;
        uint8_t sB[4]; memcpy(sB, &snddId, 4);
        buffer.insert(buffer.end(), {'S', 'N', 'D', 'D', 0x04, 0x00});
        buffer.insert(buffer.end(), sB, sB + 4);

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "ARMO");
        assert(rec.getTlvFormID("BIDS") == 0x87654321);
        assert(rec.getTlvFormID("SNDD") == 0xDEADBEEF);
    }

    // ITEM (MISC) Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'I', 'T', 'E', 'M' };
        uint32_t flags = 0x123;
        uint8_t fB[4]; memcpy(fB, &flags, 4);
        buffer.insert(buffer.end(), {'F', 'L', 'A', 'G', 0x04, 0x00});
        buffer.insert(buffer.end(), fB, fB + 4);
        buffer.insert(buffer.end(), {'N', 'N', 'A', 'M', 0x04, 0x00, 'S', 'H', 'O', 'T'});
        
        uint32_t cushVal = 0xAA;
        uint8_t cB[4]; memcpy(cB, &cushVal, 4);
        buffer.insert(buffer.end(), {'C', 'U', 'S', 'H', 0x04, 0x00});
        buffer.insert(buffer.end(), cB, cB + 4);

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "ITEM");
        assert(rec.getTlvUint32("FLAG") == 0x123);
        assert(rec.getTlvString("NNAM") == "SHOT");
        assert(rec.getTlvUint32("CUSH") == 0xAA);
    }
    std::cout << "Pass!" << std::endl;
}

void test_further_expanded_records() {

    std::cout << "Testing Further Expanded Records..." << std::endl;

    // MISC Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'M', 'I', 'S', 'C' };
        uint32_t flags = 0xABC;
        uint8_t fB[4]; memcpy(fB, &flags, 4);
        buffer.insert(buffer.end(), {'F', 'L', 'A', 'G', 0x04, 0x00});
        buffer.insert(buffer.end(), fB, fB + 4);
        buffer.insert(buffer.end(), {'N', 'N', 'A', 'M', 0x04, 0x00, 'M', 'I', 'S', 'C'});

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "MISC");
        assert(rec.getTlvUint32("FLAG") == 0xABC);
        assert(rec.getTlvString("NNAM") == "MISC");
    }

    // KEYM Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'K', 'E', 'Y', 'M' };
        uint32_t flags = 0xDEF;
        uint8_t fB[4]; memcpy(fB, &flags, 4);
        buffer.insert(buffer.end(), {'F', 'L', 'A', 'G', 0x04, 0x00});
        buffer.insert(buffer.end(), fB, fB + 4);
        buffer.insert(buffer.end(), {'N', 'N', 'A', 'M', 0x04, 0x00, 'K', 'E', 'Y', 'S'});

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "KEYM");
        assert(rec.getTlvUint32("FLAG") == 0xDEF);
        assert(rec.getTlvString("NNAM") == "KEYS");
    }

    // SCOL Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'S', 'C', 'O', 'L' };
        uint32_t color = 0x11223344;
        uint8_t cB[4]; memcpy(cB, &color, 4);
        buffer.insert(buffer.end(), {'C', 'N', 'A', 'M', 0x04, 0x00});
        buffer.insert(buffer.end(), cB, cB + 4);
        uint32_t flags = 0x55667788;
        uint8_t fB[4]; memcpy(fB, &flags, 4);
        buffer.insert(buffer.end(), {'F', 'N', 'A', 'M', 0x04, 0x00});
        buffer.insert(buffer.end(), fB, fB + 4);

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "SCOL");
        assert(rec.getTlvUint32("CNAM") == 0x11223344);
        assert(rec.getTlvUint32("FNAM") == 0x55667788);
    }

    // STAT Test
    {
        std::vector<uint8_t> buffer = { 'E', 'D', 'I', 'D', 0x04, 0x00, 'S', 'T', 'A', 'T' };
        buffer.insert(buffer.end(), {'F', 'U', 'L', 'L', 0x04, 0x00, 'S', 'T', 'A', 'T'});

        RecordHeader h; h.dataSize = buffer.size();
        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), h);
        assert(rec.getTlvString("EDID") == "STAT");
        assert(rec.getTlvString("FULL") == "STAT");
    }
    std::cout << "Pass!" << std::endl;
}

int main() {
    test_parse_string();
    test_parse_int();
    test_parse_float();
    test_mixed_record();
    test_expanded_records();
    test_further_expanded_records();
    std::cout << "\nAll tests passed successfully!" << std::endl;
    return 0;
}
