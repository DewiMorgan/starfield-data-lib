#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include "schema.hpp"

struct RecordHeader {
    char sig[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t formId;
    uint32_t vcs1;
    uint16_t version;
    uint16_t vcs2;
};

struct SubRecord {
    std::string sig;
    std::vector<uint8_t> data;
};

class StarfieldRecord {
public:
    RecordHeader header;
    uint64_t offset;
    std::map<std::string, std::vector<uint8_t>> tlvFields;
    std::vector<SubRecord> subRecords;

    std::string getTlvString(const std::string& tag) const;
    uint32_t getTlvUint32(const std::string& tag) const;
    float getTlvFloat(const std::string& tag) const;
    uint32_t getTlvFormID(const std::string& tag) const;
};

class Parser {
public:
    static StarfieldRecord parseRecord(const uint8_t* buffer, size_t size, const RecordHeader& header, uint64_t offset = 0);
};

#endif
