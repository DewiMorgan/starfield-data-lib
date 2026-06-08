#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include "core/parser.hpp"
#include "core/schema.hpp"
#include "core/vfs.hpp"
#include "db/mysql_client.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " --edid <editorid>" << std::endl;
        return 1;
    }

    std::string edid = argv[2];

    DbConfig config = MySQLClient::loadConfig();

    MySQLClient db(config);
    if (!db.connect()) {
        std::cerr << "Database connection failed." << std::endl;
        return 1;
    }

    // Query the database for the record
    std::string query = "SELECT s.path, r.offset, r.size, r.signature FROM records r "
                        "JOIN sources s ON r.source_id = s.id "
                        "JOIN edids e ON r.source_id = e.source_id AND r.offset = e.offset "
                        "WHERE e.edid = '" + edid + "' LIMIT 1;";

    auto results = db.query(query);
    if (results.empty()) {
        std::cerr << "Record not found: " << edid << std::endl;
        return 1;
    }

    auto row = results[0];
    std::string filePath = row[0];
    uint64_t offset = std::stoull(row[1]);
    uint32_t size = std::stoul(row[2]);
    std::string sig = row[3];

    try {
        std::unique_ptr<IReadStream> stream = std::make_unique<FileReadStream>(filePath);
        stream->seek(offset);

        RecordHeader header;
        if (stream->read(&header, sizeof(RecordHeader)) < sizeof(RecordHeader)) {
            throw std::runtime_error("Failed to read record header");
        }

        std::vector<uint8_t> buffer(header.dataSize);
        if (stream->read(buffer.data(), header.dataSize) < header.dataSize) {
            throw std::runtime_error("Failed to read record data");
        }

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
        std::cerr << "Error reading record: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
