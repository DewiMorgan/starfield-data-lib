#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <filesystem>
#include "core/vfs.hpp"
#include "core/parser.hpp"
#include "core/record.hpp"
#include "core/esm_writer.hpp"

using namespace starfield::core;

struct Config {
    std::string inputFile;
    std::string outputFile;
    std::string targetEdid;
    std::string targetTag;
    std::string value;
    std::string type = "string";
};

void printUsage() {
    std::cout << "Usage: sdl_modify --file <in.esm> --out <out.esm> --edid <EDID> --tag <TAG> --value <VAL> [--type <string|int|float>]\n";
}

int main(int argc, char* argv[]) {
    Config cfg;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) cfg.inputFile = argv[++i];
        else if (arg == "--out" && i + 1 < argc) cfg.outputFile = argv[++i];
        else if (arg == "--edid" && i + 1 < argc) cfg.targetEdid = argv[++i];
        else if (arg == "--tag" && i + 1 < argc) cfg.targetTag = argv[++i];
        else if (arg == "--value" && i + 1 < argc) cfg.value = argv[++i];
        else if (arg == "--type" && i + 1 < argc) cfg.type = argv[++i];
    }

    if (cfg.inputFile.empty() || cfg.outputFile.empty() || cfg.targetEdid.empty() || cfg.targetTag.empty() || cfg.value.empty()) {
        printUsage();
        return 1;
    }

    try {
        std::cout << "Loading " << cfg.inputFile << "...\n";
        auto stream = std::make_unique<FileReadStream>(cfg.inputFile);
        
        // Validate ESM Header
        char magic[4];
        stream->read(magic, 4);
        if (std::string(magic, 4) != "TES4") {
            std::cerr << "Error: Not a valid Starfield ESM file (Missing TES4 magic).\n";
            return 1;
        }

        // Skip to records (28 bytes)
        stream->seek(28); 

        std::vector<std::shared_ptr<Record>> records;
        int recordCount = 0;

        // Read records until the end of the stream
        while (true) {
            // 1. Read the RecordHeader (24 bytes)
            std::vector<uint8_t> headerBytes(24);
            if (stream->read(headerBytes.data(), 24) != 24) break;

            // 2. Extract data size from header (offset 4)
            uint32_t dataSize = 0;
            std::memcpy(&dataSize, &headerBytes[4], 4);

            // 3. Read the actual data
            std::vector<uint8_t> dataBytes(dataSize);
            if (stream->read(dataBytes.data(), dataSize) != dataSize) break;

            // 4. Combine header and data for the parser
            std::vector<uint8_t> fullBlob = headerBytes;
            fullBlob.insert(fullBlob.end(), dataBytes.begin(), dataBytes.end());

            // 5. Parse into Record object
            auto recOpt = Record::parse(fullBlob);
            if (recOpt) {
                records.push_back(std::make_shared<Record>(*recOpt));
                recordCount++;
            }
        }

        std::cout << "Parsed " << recordCount << " records. Searching for " << cfg.targetEdid << "...\n";

        bool found = false;
        for (auto& rec : records) {
            if (rec->getString("EDID").value_or("") == cfg.targetEdid) {
                std::cout << "Found record! Updating tag " << cfg.targetTag << "...\n";
                
                if (cfg.type == "int") {
                    rec->setTlvInt32(cfg.targetTag, std::stoi(cfg.value));
                } else if (cfg.type == "float") {
                    rec->setTlvFloat(cfg.targetTag, std::stof(cfg.value));
                } else {
                    rec->setTlvString(cfg.targetTag, cfg.value);
                }
                
                found = true;
                break;
            }
        }

        if (!found) {
            std::cerr << "Error: Record with EDID " << cfg.targetEdid << " not found.\n";
            return 1;
        }

        std::cout << "Packing into " << cfg.outputFile << "...\n";
        ESMWriter writer;
        writer.write(cfg.outputFile, records);

        std::cout << "Success! Modified ESM created.\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
