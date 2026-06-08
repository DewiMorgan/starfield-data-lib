#pragma once

#include <vector>
#include <cstdint>
#include "record.hpp"

namespace starfield::core {

class RecordWriter {
public:
    /**
     * Serializes a Record object back into its raw binary representation.
     * @param rec The record to serialize.
     * @return A vector of bytes containing the full serialized record (header + TLVs).
     */
    static std::vector<uint8_t> serialize(const Record& rec);
};

} // namespace starfield::core
