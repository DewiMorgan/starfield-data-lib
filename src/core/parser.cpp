#include "parser.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>

std::string StarfieldRecord::getTlvString(const std::string& tag) const {
    for (const auto& entry : tlvFields) {
        if (entry.tag == tag) {
            if (entry.offset + entry.length > rawData.size()) return "";
            std::string s(reinterpret_cast<const char*>(&rawData[entry.offset]), entry.length);
            size_t nullPos = s.find('\0');
            if (nullPos != std::string::npos) s = s.substr(0, nullPos);
            return s;
        }
    }
    return "";
}

uint32_t StarfieldRecord::getTlvUint32(const std::string& tag) const {
    for (const auto& entry : tlvFields) {
        if (entry.tag == tag) {
            if (entry.length < 4 || entry.offset + 4 > rawData.size()) return 0;
            return *reinterpret_cast<const uint32_t*>(&rawData[entry.offset]);
        }
    }
    return 0;
}

float StarfieldRecord::getTlvFloat(const std::string& tag) const {
    for (const auto& entry : tlvFields) {
        if (entry.tag == tag) {
            if (entry.length < 4 || entry.offset + 4 > rawData.size()) return 0.0f;
            return *reinterpret_cast<const float*>(&rawData[entry.offset]);
        }
    }
    return 0.0f;
}

uint32_t StarfieldRecord::getTlvFormID(const std::string& tag) const {
    return getTlvUint32(tag);
}

StarfieldRecord Parser::parseRecord(const uint8_t* buffer, size_t size, const RecordHeader& header, uint64_t offset) {
    StarfieldRecord rec;
    rec.header = header;
    rec.offset = offset;
    rec.rawData.assign(buffer, buffer + size);

    size_t pos = 0;
    try {
        while (pos + 6 <= size) {
            char tag[4];
            memcpy(tag, &buffer[pos], 4);
            uint16_t len = 0;
            memcpy(&len, &buffer[pos + 4], 2);
            
            bool isAlphanumeric = true;
            for(int i=0; i<4; ++i) if(!isalnum(static_cast<unsigned char>(tag[i]))) isAlphanumeric = false;

            if (isAlphanumeric && (size - (pos + 6) >= len)) {
                rec.tlvFields.push_back({std::string(tag, 4), pos + 6, len});
                pos += 6 + len;
            } else {
                std::string subSig(tag, 4);
                std::vector<uint8_t> subData;
                if (pos < size) {
                    subData.assign(buffer + pos, buffer + size);
                }
                rec.subRecords.push_back({subSig, std::move(subData)});
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[Parser] Error parsing record at " << offset << ": " << e.what() << std::endl;
    }
    return rec;
}
