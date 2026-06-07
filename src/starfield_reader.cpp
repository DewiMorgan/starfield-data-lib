#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include "schema.h"
#include "parser.h"

struct RecordHeader {
    char sig[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t formId;
    uint32_t vcs1;
    uint16_t version;
    uint16_t vcs2;
};

class StarfieldReader {
public:
    std::string filePath;

    StarfieldReader(const std::string& path) : filePath(path) {}

    bool readHeader(std::ifstream& is, RecordHeader& header, uint64_t& offset) {
        offset = is.tellg();
        is.read(reinterpret_cast<char*>(&header), sizeof(RecordHeader));
        return is.gcount() == sizeof(RecordHeader);
    }

    StarfieldRecord parseRecord(std::ifstream& is, const RecordHeader& header, uint64_t offset) {
        std::vector<uint8_t> buffer(header.dataSize);
        is.read(reinterpret_cast<char*>(buffer.data()), header.dataSize);
        return Parser::parseRecord(buffer.data(), buffer.size(), header, offset);
    }

    void index(std::ostream& out) {
        std::ifstream is(filePath, std::ios::binary);
        if (!is) {
            std::cerr << "Cannot open file: " << filePath << std::endl;
            return;
        }

        RecordHeader header;
        uint64_t offset;
        while (readHeader(is, header, offset)) {
            if (std::string(header.sig, 4) != "GRUP") {
                StarfieldRecord rec = parseRecord(is, header, offset);
                std::string edid = rec.getTlvString("EDID");
                if (!edid.empty()) {
                    out << "INSERT INTO edids (form_id, signature, offset, edid) VALUES (" 
                        << header.formId << ", '" << std::string(header.sig, 4) << "', " 
                        << offset << ", '" << edid << "') ON DUPLICATE KEY UPDATE edid='" << edid << "';\n";
                }
            } else {
                is.seekg(header.dataSize, std::ios::cur);
            }
        }
    }

    void printRecord(uint64_t offset) {
        std::ifstream is(filePath, std::ios::binary);
        is.seekg(offset);

        RecordHeader header;
        if (!readHeader(is, header, offset)) return;

        StarfieldRecord rec = parseRecord(is, header, offset);
        
        std::string sig(header.sig, 4);
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Record: " << sig << " | Offset: 0x" << std::hex << offset << std::dec << std::endl;
        std::cout << "FormID: 0x" << std::hex << header.formId << std::dec << std::endl;
        
        std::cout << "\n--- Fields ---" << std::endl;
        
        // Check for specific record schema
        const RecordSchema* schema = nullptr;
        if (g_RecordSchemas.count(sig)) {
            schema = &g_RecordSchemas[sig];
        }

        for (auto const& [tag, data] : rec.tlvFields) {
            std::string label = "";
            FieldType type = FieldType::Unknown;

            // 1. Check record-specific schema
            if (schema && schema->tags.count(tag)) {
                label = schema->tags.at(tag).label;
                type = schema->tags.at(tag).type;
            } 
            // 2. Check common tags
            else if (g_CommonTags.count(tag)) {
                label = g_CommonTags.at(tag).label;
                type = g_CommonTags.at(tag).type;
            }

            std::cout << (label.empty() ? tag : label + " (" + tag + ")") << ": ";

            if (type == FieldType::String) {
                std::string s(data.begin(), data.end());
                size_t nullPos = s.find('\0');
                if (nullPos != std::string::npos) s = s.substr(0, nullPos);
                std::cout << s;
            } else if (type == FieldType::Int32) {
                if (data.size() >= 4) std::cout << *reinterpret_cast<const int32_t*>(data.data());
                else std::cout << "[Invalid Size]";
            } else if (type == FieldType::Float) {
                if (data.size() >= 4) std::cout << *reinterpret_cast<const float*>(data.data());
                else std::cout << "[Invalid Size]";
            } else if (type == FieldType::FormID) {
                if (data.size() >= 4) std::cout << "0x" << std::hex << *reinterpret_cast<const uint32_t*>(data.data()) << std::dec;
                else std::cout << "[Invalid Size]";
            } else {
                // Hex dump for unknown/unmapped tags
                std::cout << "[Raw] ";
                for (auto b : data) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b << " ";
                std::cout << std::dec;
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------------------------------------------" << std::endl;
    }
};

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <file> <mode> [offset]\n";
        std::cerr << "Modes: --index, --dump <offset>\n";
        return 1;
    }

    std::string file = argv[1];
    std::string mode = argv[2];
    StarfieldReader reader(file);

    if (mode == "--index") {
        reader.index(std::cout);
    } else if (mode == "--dump" && argc == 4) {
        uint64_t offset = std::stoull(argv[3], nullptr, 0);
        reader.printRecord(offset);
    } else {
        std::cerr << "Invalid mode or missing offset.\n";
        return 1;
    }

    return 0;
}
