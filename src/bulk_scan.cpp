#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iomanip>
#include "parser.h"

namespace fs = std::filesystem;

void process_file(const fs::path& filePath) {
    std::string fileName = filePath.filename().string();
    std::ifstream is(filePath, std::ios::binary);
    if (!is) {
        std::cerr << "Failed to open: " << filePath << std::endl;
        return;
    }

    uint64_t offset = 0;
    while (is) {
        RecordHeader header;
        if (!is.read(reinterpret_cast<char*>(&header), sizeof(RecordHeader))) break;

        std::vector<uint8_t> buffer(header.dataSize);
        if (!is.read(reinterpret_cast<char*>(buffer.data()), header.dataSize)) break;

        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, offset);

        // Find EDID using schema
        std::string edid = "";
        std::string sig(rec.header.sig, 4);
        auto it = g_RecordSchemas.find(sig);
        if (it != g_RecordSchemas.end()) {
            for (const auto& field : it->second) {
                if (field.first == "EDID") {
                    edid = rec.getTlvString("EDID");
                    break;
                }
            }
        }

        // TSV Output: plugin_name \t offset \t signature \t formid \t size \t edid
        std::cout << fileName << "\t" 
                  << offset << "\t" 
                  << sig << "\t" 
                  << rec.header.formId << "\t" 
                  << header.dataSize << "\t" 
                  << edid << "\n";

        offset += sizeof(RecordHeader) + header.dataSize;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <data_folder>" << std::endl;
        return 1;
    }

    std::string dataFolder = argv[1];
    try {
        for (const auto& entry : fs::directory_iterator(dataFolder)) {
            std::string ext = entry.path().extension().string();
            if (ext == ".esm" || ext == ".esp") {
                process_file(entry.path());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error scanning folder: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
