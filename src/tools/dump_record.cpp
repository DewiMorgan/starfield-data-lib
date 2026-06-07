#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>

struct RecordHeader {
    char signature[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t formID;
    uint32_t vcs1;
    uint16_t version;
    uint16_t vcs2;

    static constexpr size_t SIZE = 24;
};

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) return 1;

    RecordHeader header;
    while (file.read(reinterpret_cast<char*>(&header), RecordHeader::SIZE)) {
        if (std::string(header.signature, 4) == "KYWD") {
            std::cout << "KYWD Record at 0x" << std::hex << file.tellg() - RecordHeader::SIZE << std::endl;
            
            std::vector<uint8_t> buffer(header.dataSize);
            file.read(reinterpret_cast<char*>(buffer.data()), header.dataSize);
            
            for (size_t i = 0; i < buffer.size(); ++i) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i] << " ";
                if ((i + 1) % 16 == 0) std::cout << std::endl;
            }
            std::cout << std::endl;
            break; // Just the first one
        } else {
            file.seekg(header.dataSize, std::ios::cur);
        }
    }
    return 0;
}
