#include "record_writer.hpp"
#include "parser.hpp"
#include <cstring>
#include <algorithm>

namespace starfield::core {

std::vector<uint8_t> RecordWriter::serialize(const Record& rec) {
    std::vector<uint8_t> blob;
    
    // 1. Construct the Header
    std::vector<uint8_t> headerBlob = rec.getHeader();
    
    // Calculate total data size (sum of all TLVs)
    uint32_t dataSize = 0;
    for (const auto& [tag, tlv] : rec.getTlvs()) {
        dataSize += 4 + 2 + tlv.size();
    }
    
    // Patch the dataSize into the header blob (offset 16)
    if (headerBlob.size() >= 20) {
        std::memcpy(headerBlob.data() + 16, &dataSize, 4);
    }

    // Write header to blob
    blob = headerBlob;

    // 2. Write TLVs
    for (const auto& [tag, tlv] : rec.getTlvs()) {
        // Tag (4 bytes)
        std::string tagStr = tag;
        while(tagStr.length() < 4) tagStr += ' ';
        for(int i=0; i<4; ++i) blob.push_back(tagStr[i]);

        // Length (2 bytes, little endian)
        uint16_t len = static_cast<uint16_t>(tlv.size());
        uint8_t lenBytes[2];
        std::memcpy(lenBytes, &len, 2);
        blob.push_back(lenBytes[0]);
        blob.push_back(lenBytes[1]);

        // Value
        blob.insert(blob.end(), tlv.begin(), tlv.end());
    }

    return blob;
}

} // namespace starfield::core
