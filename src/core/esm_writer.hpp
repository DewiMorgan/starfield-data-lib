#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "record.hpp"

namespace starfield::core {

class ESMWriter {
public:
    ESMWriter() = default;

    /**
     * Writes a collection of records to a file, prefixed with the ESM header.
     * @param path Destination file path.
     * @param records The list of records to serialize.
     * @return True if successful.
     */
    bool write(const std::string& path, const std::vector<std::shared_ptr<Record>>& records);

private:
    // The Starfield ESM header is currently observed to be a simple 4-byte 
    // "TES4" magic string followed by versioning/padding in some versions.
    // For the MVP, we will implement the observed layout of the current game files.
    void writeHeader(std::ostream& os);
};

} // namespace starfield::core
