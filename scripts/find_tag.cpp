#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "core/parser.hpp"
#include "core/record.hpp"

int main() {
    std::ifstream file("vendor/Bethesda/CwLemonade.esm", std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    file.seekg(24, std::ios::beg);

    int recordCount = 0;
    while (file) {
        std::vector<uint8_t> headerBuf(24);
        if (!file.read((char*)headerBuf.data(), 24)) break;

        uint32_t dataSize = *(uint32_t*)(&headerBuf[4]);
        std::vector<uint8_t> recordBuf(24 + dataSize);
        std::copy(headerBuf.begin(), headerBuf.end(), recordBuf.begin());
        
        if (dataSize > 0) {
            file.read((char*)recordBuf.data() + 24, dataSize);
        }

        auto recOpt = starfield::core::Record::parse(recordBuf);
        if (recOpt) {
            recordCount++;
            std::cout << "Processing record " << recordCount << " at offset " << file.tellg() << std::endl;
            auto& rec = *recOpt;
            std::cout << "Record " << recordCount << " (" << rec.getSignature() << "):" << std::endl;
            for (auto const& entry : rec.getTlvs()) {
                auto valOpt = rec.getString(entry.tag);
                if (valOpt) {
                    std::cout << "  [" << entry.tag << "] " << *valOpt << std::endl;
                    if (valOpt->find("CraftedFood_Container_BulletCoffee.nif") != std::string::npos) {
                        std::cout << "!!! FOUND IT !!!" << std::endl;
                        return 0;
                    }
                } else {
                    std::cout << "  [" << entry.tag << "] (non-string)" << std::endl;
                }
            }
        }
    }

    return 0;
}
