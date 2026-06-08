#include "esm_writer.hpp"
#include <iostream>

namespace starfield::core {

void ESMWriter::writeHeader(std::ostream& os) {
    // The ESM file header is simply the first record (TES4 record).
    // No additional magic string is required here.
}

bool ESMWriter::write(const std::string& path, const std::vector<std::shared_ptr<Record>>& records) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) {
        return false;
    }

    try {
        writeHeader(ofs);

        for (const auto& record : records) {
            std::vector<uint8_t> blob = record->serialize();
            ofs.write(reinterpret_cast<const char*>(blob.data()), blob.size());
        }
    } catch (const std::exception& e) {
        return false;
    }

    return ofs.good();
}

} // namespace starfield::core
