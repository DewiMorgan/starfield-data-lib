#include "parser.hpp"
#include <cstring>
#include <algorithm>

std::string StarfieldRecord::getTlvString(const std::string& tag) const {
    auto it = tlvFields.find(tag);
    if (it == tlvFields.end()) return "";
    std::string s(it->second.begin(), it->second.end());
    size_t nullPos = s.find('\0');
    if (nullPos != std::string::npos) s = s.substr(0, nullPos);
    return s;
}

uint32_t StarfieldRecord::getTlvUint32(const std::string& tag) const {
    auto it = tlvFields.find(tag);
    if (it == tlvFields.end() || it->second.size() < 4) return 0;
    return *reinterpret_cast<const uint32_t*>(it->second.data());
}

float StarfieldRecord::getTlvFloat(const std::string& tag) const {
    auto it = tlvFields.find(tag);
    if (it == tlvFields.end() || it->second.size() < 4) return 0.0f;
    return *reinterpret_cast<const float*>(it->second.data());
}

uint32_t StarfieldRecord::getTlvFormID(const std::string& tag) const {
    return getTlvUint32(tag);
}

StarfieldRecord Parser::parseRecord(const uint8_t* buffer, size_t size, const RecordHeader& header, uint64_t offset) {
    StarfieldRecord rec;
    rec.header = header;
    rec.offset = offset;

    size_t pos = 0;
    while (pos + 6 <= size) {
        char tag[4];
        memcpy(tag, &buffer[pos], 4);
        uint16_t len = *reinterpret_cast<const uint16_t*>(&buffer[pos + 4]);
        
        bool isAlphanumeric = true;
        for(int i=0; i<4; ++i) if(!isalnum(static_cast<unsigned char>(tag[i]))) isAlphanumeric = false;

        if (isAlphanumeric && pos + 6 + len <= size) {
            std::string tagStr(tag, 4);
            std::vector<uint8_t> data(buffer + pos + 6, buffer + pos + 6 + len);
            rec.tlvFields[tagStr] = data;
            pos += 6 + len;
        } else {
            std::string subSig(tag, 4);
            rec.subRecords.push_back({subSig, std::vector<uint8_t>(buffer + pos, buffer + size)});
            break;
        }
    }
    return rec;
}
