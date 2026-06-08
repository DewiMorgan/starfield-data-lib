#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>
#include "parser.hpp"

namespace starfield::core {

struct TlvEntry {
    std::string tag;
    std::vector<uint8_t> data;
};

class Record {
public:
    Record() = default;
    
    // Parse a raw binary blob into a Record object
    static std::optional<Record> parse(const std::vector<uint8_t>& data);

    // Header Info
    const std::string& getSignature() const { return signature; }
    uint32_t getDataSize() const { return dataSize; }
    const std::vector<uint8_t>& getHeader() const { return header; }

    // Value Access
    std::optional<std::vector<uint8_t>> getTlvData(const std::string& tag) const;
    std::optional<std::string> getString(const std::string& tag) const;
    std::optional<int32_t> getInt32(const std::string& tag) const;
    std::optional<float> getFloat(const std::string& tag) const;

    // Mutation
    void setTlv(const std::string& tag, const std::vector<uint8_t>& data);
    void setTlvString(const std::string& tag, const std::string& value);
    void setTlvInt32(const std::string& tag, int32_t value);
    void setTlvFloat(const std::string& tag, float value);
    void removeTlv(const std::string& tag);

    // Traversal
    const std::vector<TlvEntry>& getTlvs() const { return tlvs; }
    bool hasTag(const std::string& tag) const {
        for (const auto& entry : tlvs) if (entry.tag == tag) return true;
        return false;
    }

    // Binary Assembly
    std::vector<uint8_t> serialize() const;

private:
    std::string signature;
    uint32_t dataSize = 0;
    std::vector<uint8_t> header; // Exactly 24 bytes
    std::vector<TlvEntry> tlvs;
};

} // namespace starfield::core
