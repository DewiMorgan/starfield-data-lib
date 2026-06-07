#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <memory>
#include "parser.h"
#include "schema.h"

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " --edid <editorid>" << std::endl;
        return 1;
    }

    std::string edid = argv[2];
    std::string query = "mysql -u root -proot starfield -N -s -e \"SELECT r.file, r.offset, r.size, r.signature FROM records r JOIN edids e ON r.form_id = e.form_id AND r.file = e.file WHERE e.edid = '" + edid + "';\"";
    
    std::string output = exec(query.c_str());
    if (output.empty()) {
        std::cerr << "Record not found: " << edid << std::endl;
        return 1;
    }

    std::vector<std::string> parts;
    size_t start = 0, end = 0;
    while ((end = output.find('\t', start)) != std::string::npos) {
        parts.push_back(output.substr(start, end - start));
        start = end + 1;
    }
    parts.push_back(output.substr(start));

    if (parts.size() < 4) {
        std::cerr << "Unexpected DB output: " << output << std::endl;
        return 1;
    }

    std::string file = parts[0];
    uint64_t offset = std::stoull(parts[1]);
    uint32_t size = std::stoul(parts[2]);
    std::string sig = parts[3];

    if (!sig.empty() && sig.back() == '\n') sig.pop_back();
    if (!sig.empty() && sig.back() == '\r') sig.pop_back();

    try {
        std::ifstream inputStream("/mnt/c/Games/Steam/steamapps/common/Starfield/Data/" + file, std::ios::binary);
        if (!inputStream) throw std::runtime_error("Could not open file");

        inputStream.seekg(offset);
        RecordHeader header;
        inputStream.read(reinterpret_cast<char*>(&header), sizeof(RecordHeader));

        std::vector<uint8_t> buffer(header.dataSize);
        inputStream.read(reinterpret_cast<char*>(buffer.data()), header.dataSize);

        StarfieldRecord rec = Parser::parseRecord(buffer.data(), buffer.size(), header, offset);

        std::cout << "Record Found: " << sig << " | Offset: 0x" << std::hex << offset << std::dec << std::endl;
        if (sig == "WEAP") {
            std::cout << "--- Weapon Summary ---" << std::endl;
            std::cout << "EDID: " << rec.getTlvString("EDID") << std::endl;
            std::cout << "Full Name: " << rec.getTlvString("FULL") << std::endl;
            
            auto wdmg = rec.tlvFields.find("WDMG");
            if (wdmg != rec.tlvFields.end() && wdmg->second.size() >= 12) {
                float base = *reinterpret_cast<const float*>(wdmg->second.data());
                float minR = *reinterpret_cast<const float*>(wdmg->second.data() + 4);
                float maxR = *reinterpret_cast<const float*>(wdmg->second.data() + 8);
                std::cout << "Base Damage: " << base << std::endl;
                std::cout << "Range: " << minR << " - " << maxR << std::endl;
            }
            
            auto wgen = rec.tlvFields.find("WGEN");
            if (wgen != rec.tlvFields.end() && wgen->second.size() >= 12) {
                float weight = *reinterpret_cast<const float*>(wgen->second.data() + 4);
                uint32_t value = *reinterpret_cast<const uint32_t*>(wgen->second.data() + 8);
                std::cout << "Weight: " << weight << std::endl;
                std::cout << "Value: " << value << std::endl;
            }
            std::cout << "----------------------" << std::endl;
        } else {
            std::cout << "--------------------------------------------------" << std::endl;
            for (auto const& [tag, data] : rec.tlvFields) {
                std::cout << tag << " (" << data.size() << " bytes): ";
                std::string s = rec.getTlvString(tag);
                if (!s.empty()) {
                    std::cout << s << std::endl;
                } else {
                    std::cout << "[Binary Data] ";
                    for (auto b : data) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b << " ";
                    std::cout << std::dec << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
