#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include "vfs.hpp"

namespace starfield {

class Extractor {
public:
    explicit Extractor(std::shared_ptr<IReadStream> stream);

    /**
     * Extracts a raw record blob given its starting offset.
     * Reads the record header to determine the size, then returns the full blob.
     */
    std::vector<uint8_t> extractRecord(uint64_t offset);

    /**
     * Extracts a raw record blob and writes it directly to a file.
     */
    bool extractToFile(uint64_t offset, const std::string& outputPath);

private:
    std::shared_ptr<IReadStream> m_stream;
};

} // namespace starfield
