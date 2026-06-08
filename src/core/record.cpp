#include "record.hpp"
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace starfield::core {

std::optional<Record> Record::parse(const std::vector<uint8_t>& data) {
    if (data.size() < 24) return std::nullopt;

    Record rec;
    
    // Capture the full 24-byte header
    rec.header = std::vector<uint8_t>(data.begin(), data.begin() + 24);

    char sigBuf[5] = {0};
    std::memcpy(sigBuf, data.data(), 4);
    rec.signature = sigBuf;

    uint32_t size;
    std::memcpy(&size, data.data() + 4, 4);
    rec.dataSize = size;

    // Parse TLVs into the vector to preserve order
    size_t offset = 24;
    size_t end = std::min(data.size(), (size_t)(24 + rec.dataSize));

    while (offset + 6 <= end) {
        char tagBuf[5] = {0};
        std::memcpy(tagBuf, data.data() + offset, 4);
        std::string tag = tagBuf;

        uint16_t length;
        std::memcpy(&length, data.data() + offset + 4, 2);

        if (offset + 6 + length > data.size()) {
            std::cerr << "[Parser] Buffer overflow detected: offset=" << offset << " len=" << length << " size=" << data.size() << std::endl;
            break;
        }

        std::vector<uint8_t> value(data.begin() + offset + 6, data.begin() + offset + 6 + length);
        rec.tlvs.push_back({tag, value});

        offset += 6 + length;
    }

    return rec;
}

std::optional<std::vector<uint8_t>> Record::getTlvData(const std::string& tag) const {
    for (const auto& entry : tlvs) {
        if (entry.tag == tag) return entry.data;
    }
    return std::nullopt;
}

std::optional<std::string> Record::getString(const std::string& tag) const {
    auto data = getTlvData(tag);
    if (!data) return std::nullopt;

    const char* start = reinterpret_cast<const char*>(data->data());
    size_t len = data->size();
    for (size_t i = 0; i < len; ++i) {
        if (start[i] == '\0') {
            len = i;
            break;
        }
    }
    return std::string(start, len);
}

std::optional<int32_t> Record::getInt32(const std::string& tag) const {
    auto data = getTlvData(tag);
    if (!data || data->size() < 4) return std::nullopt;

    int32_t val;
    std::memcpy(&val, data->data(), 4);
    return val;
}

std::optional<float> Record::getFloat(const std::string& tag) const {
    auto data = getTlvData(tag);
    if (!data || data->size() < 4) return std::nullopt;

    float val;
    std::memcpy(&val, data->data(), 4);
    return val;
}

void Record::setTlv(const std::string& tag, const std::vector<uint8_t>& data) {
    for (auto& entry : tlvs) {
        if (entry.tag == tag) {
            entry.data = data;
            return;
        }
    }
    tlvs.push_back({tag, data});
}

void Record::setTlvString(const std::string& tag, const std::string& value) {
    std::vector<uint8_t> data(value.begin(), value.end());
    data.push_back(0); // Null terminator
    setTlv(tag, data);
}

void Record::setTlvInt32(const std::string& tag, int32_t value) {
    std::vector<uint8_t> data(4);
    std::memcpy(data.data(), &value, 4);
    setTlv(tag, data);
}

void Record::setTlvFloat(const std::string& tag, float value) {
    std::vector<uint8_t> data(4);
    std::memcpy(data.data(), &value, 4);
    setTlv(tag, data);
}

void Record::removeTlv(const std::string& tag) {
    tlvs.erase(std::remove_if(tlvs.begin(), tlvs.end(), 
               [&](const TlvEntry& e) { return e.tag == tag; }), tlvs.end());
}

std::vector<uint8_t> Record::serialize() const {
    std::vector<uint8_t> output = header;
    
    uint32_t totalDataSize = 0;
    std::vector<uint8_t> payload;

    for (const auto& entry : tlvs) {
        // Tag (4 bytes)
        char tagBuf[4];
        std::memcpy(tagBuf, entry.tag.data(), std::min(entry.tag.size(), (size_t)4));
        if (entry.tag.size() < 4) std::memset(tagBuf + entry.tag.size(), 0, 4 - entry.tag.size());
        
        payload.insert(payload.end(), tagBuf, tagBuf + 4);

        // Length (2 bytes)
        uint16_t length = static_cast<uint16_t>(entry.data.size());
        uint8_t lenBuf[2];
        std::memcpy(lenBuf, &length, 2);
        payload.insert(payload.end(), lenBuf, lenBuf + 2);

        // Value
        payload.insert(payload.end(), entry.data.begin(), entry.data.end());
        
        totalDataSize += 6 + length;
    }

    // Update size in the header (offset 4)
    std::memcpy(output.data() + 4, &totalDataSize, 4);
    
    // Append payload
    output.insert(output.end(), payload.begin(), payload.end());

    return output;
}

} // namespace starfield::core
