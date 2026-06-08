#include "esm_writer.hpp"
#include <iostream>

namespace starfield::core {

void ESMWriter::writeHeader(std::ostream& os) {
    // Based on observed Starfield ESM files:
    // The file starts with the "TES4" magic identifier.
    os.write("TES4", 4);
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
