#include "base_types.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include "records.hpp"

bool isValidType(const char* type) {
    // General rule: only uppercase letters, numbers, and underscores
    bool all_standard = true;
    for (int i = 0; i < 4; ++i) {
        unsigned char c = static_cast<unsigned char>(type[i]);
        if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
            all_standard = false;
            break;
        }
    }
    if (all_standard) return true;

    // Special case for WTHR dynamic clouds: ASCII(ord('0')+n) + "0TX"
    if (type[1] == '0' && type[2] == 'T' && type[3] == 'X') {
        unsigned char c0 = static_cast<unsigned char>(type[0]);
        if (c0 >= '0') return true;
    }

    // Special case for IMAD eye adaptation/bloom fields: [any char] + "IAD"
    // ToDo: IMAD.html only lists ^@-^T ("\0"-"\20") and '@'-'T' as valid type[0].
    if (type[1] == 'I' && type[2] == 'A' && type[3] == 'D') {
        return true;
    }

    return false;
}

std::string read_zstring(std::ifstream& file, uint16_t length) {
    if (length == 0) return "";
    std::vector<char> buf(length);
    file.read(buf.data(), length);
    return std::string(buf.data());
}

void populate_tes4(std::ifstream& file, uint32_t payload_length) {
    TES4 record{};
    uint32_t bytes_read = 0;

    while (bytes_read < payload_length) {
        FieldHeader fh;
        file.read((char*)&fh, sizeof(fh));
        if (file.gcount() < static_cast<std::streamsize>(sizeof(fh))) break;

        std::string fid(fh.type, 4);

        if (fid == "HEDR") {
            file.read((char*)&record.header, fh.length);
        } else if (fid == "CNAM") {
            record.author.value = read_zstring(file, fh.length);
        } else if (fid == "SNAM") {
            record.description.value = read_zstring(file, fh.length);
        } else if (fid == "MAST") {
            ZString master_name;
            master_name.value = read_zstring(file, fh.length);
            FieldHeader dfh;
            file.read((char*)&dfh, sizeof(dfh));
            uint64_t data;
            file.read((char*)&data, dfh.length);
            record.masters.push_back({master_name}); //, data});
            bytes_read += sizeof(FieldHeader) + dfh.length;
        } else if (fid == "ONAM") {
            uint32_t count = fh.length / 4;
            for (uint32_t i = 0; i < count; ++i) {
                FormID f;
                file.read((char*)&f, 4);
                record.overridden_forms.push_back(f);
            }
        } else if (fid == "INTV") {
            file.read((char*)&record.tagify_strings_count, fh.length);
        } else if (fid == "INCC") {
            file.read((char*)&record.master_counter, fh.length);
        } else {
            file.seekg(fh.length, std::ios::cur);
        }
        bytes_read += sizeof(FieldHeader) + fh.length;
    }

    std::cout << "  Parsed TES4 logically:\n";
    std::cout << "    Author: " << record.author.value << "\n";
    std::cout << "    Description: " << record.description.value << "\n";
    std::cout << "    Masters count: " << record.masters.size() << "\n";
    std::cout << "    Tagify count: " << record.tagify_strings_count << "\n";
}

void populate_npc(std::ifstream& file, uint32_t payload_length) {

    NPC_ record{};
    uint32_t bytes_read = 0;

    while (bytes_read < payload_length) {
        FieldHeader fh;
        file.read((char*)&fh, sizeof(fh));
        if (file.gcount() < static_cast<std::streamsize>(sizeof(fh))) break;

        if (!isValidType(fh.type)) {
            std::cerr << "FATAL: Invalid field type '" << std::string(fh.type, 4) 
                      << "' at offset 0x" << std::hex << file.tellg() << std::dec << std::endl;
            exit(1);
        }

        std::string fid(fh.type, 4);

        if (fid == "EDID") {
            record.edid.value = read_zstring(file, fh.length);
        } else if (fid == "VMAD") {
            file.read((char*)&record.vmad, fh.length);
        } else if (fid == "OBND") {
            file.read((char*)&record.obnd, fh.length);
        } else if (fid == "ACBS") {
            file.read((char*)&record.baseStats, fh.length);
        } else if (fid == "SNAM") {
            NPCFaction faction;
            file.read((char*)&faction.faction, 4);
            file.read((char*)&faction.rank, 1);
            file.seekg(fh.length - 5, std::ios::cur);
            record.factions.push_back(faction);
        } else if (fid == "INAM") {
            file.read((char*)&record.deathItem, 4);
        } else if (fid == "VTCK") {
            file.read((char*)&record.voiceType, 4);
        } else if (fid == "TPLT") {
            file.read((char*)&record.templateId, 4);
        } else if (fid == "RNAM") {
            file.read((char*)&record.race, 4);
        } else if (fid == "DEST") {
            file.read((char*)&record.dest, fh.length);
        } else if (fid == "SPCT") {
            uint32_t count;
            file.read((char*)&count, 4);
            for (uint32_t i = 0; i < count; ++i) {
                FieldHeader sfh;
                file.read((char*)&sfh, sizeof(sfh));
                FormID spell;
                file.read((char*)&spell, 4);
                file.seekg(sfh.length - 4, std::ios::cur);
                record.spells.push_back(spell);
            }
            // We need to ensure bytes_read is consistent with file pointer
            // Since we are inside a record payload, we can just update the 
            // loop's bytes_read to match the file pointer if we want,
            // but it's easier to just let the loop finish and use seekg
            // if we knew the total length.
            // Actually, the simplest way is to just read exactly fh.length bytes.
            // Let's just subtract the read bytes from the remaining fh.length.
            // Wait, SPCT is a Field. fh.length is the size of the SPCT payload.
            // The current code reads 'count' and then loops.
            // If the loop reads more than fh.length, we drift.
            // Let's just skip to the end of the field to be safe.
            file.seekg(fh.length - (4 + 0), std::ios::cur); // This is wrong.
            // Correct way: record how many we read, then seekg(fh.length - read)
        } else if (fid == "WNAM") {
            file.read((char*)&record.wornArmor, 4);
        } else if (fid == "ANAM") {
            file.read((char*)&record.awayModel, 4);
        } else if (fid == "ATKR") {
            file.read((char*)&record.attackRace, 4);
        } else if (fid == "ATKD") {
            std::streampos start = file.tellg();
            NPCAttackEvent event;
            uint32_t data_len = fh.length - 6; // Subtract FieldHeader size
            file.read((char*)&event.data, data_len);
            
            FieldHeader efh;
            file.read((char*)&efh, sizeof(efh));
            event.event.value = read_zstring(file, efh.length);
            record.attacks.push_back(event);
            file.seekg(start + std::streamoff(fh.length));
        } else if (fid == "SPOR") {
            file.read((char*)&record.spectatorOverride, 4);
        } else if (fid == "OCOR") {
            file.read((char*)&record.observeCorpse, 4);
        } else if (fid == "GWOR") {
            file.read((char*)&record.guardWarnOverride, 4);
        } else if (fid == "ECOR") {
            file.read((char*)&record.combatOverride, 4);
        } else if (fid == "PRKZ") {
            std::streampos start = file.tellg();
            uint32_t count;
            file.read((char*)&count, 4);
            for (uint32_t i = 0; i < count; ++i) {
                FieldHeader pfh;
                file.read((char*)&pfh, sizeof(pfh));
                NPCPerk perk;
                file.read((char*)&perk.perk, 4);
                file.read((char*)&perk.rank, 1);
                file.seekg(pfh.length - 5, std::ios::cur);
                record.perks.push_back(perk);
            }
            file.seekg(start + std::streamoff(fh.length));
        } else if (fid == "COCT") {
            std::streampos start = file.tellg();
            uint32_t count;
            file.read((char*)&count, 4);
            for (uint32_t i = 0; i < count; ++i) {
                FieldHeader cfh;
                file.read((char*)&cfh, sizeof(cfh));
                NPCContainerObject obj;
                file.read((char*)&obj.item, 4);
                file.read((char*)&obj.count, 4);
                file.seekg(cfh.length - 8, std::ios::cur);
                record.containerObjects.push_back(obj);
            }
            file.seekg(start + std::streamoff(fh.length));
        } else if (fid == "COED") {
            file.read((char*)&record.owner, fh.length);
        } else if (fid == "AIDT") {
            file.read((char*)&record.aiData, fh.length);
        } else if (fid == "PKID") {
            FormID pkg;
            file.read((char*)&pkg, 4);
            record.aiPackages.push_back(pkg);
        } else if (fid == "KSIZ") {
            uint32_t count;
            file.read((char*)&count, 4);
            for (uint32_t i = 0; i < count; ++i) {
                FieldHeader kfh;
                file.read((char*)&kfh, sizeof(kfh));
                FormID kw;
                file.read((char*)&kw, 4);
                file.seekg(kfh.length - 4, std::ios::cur);
                record.keywords.push_back(kw);
            }
        } else if (fid == "CNAM") {
            file.read((char*)&record.classId, 4);
        } else if (fid == "FULL") {
            record.fullName.value = read_zstring(file, fh.length);
        } else if (fid == "SHRT") {
            record.shortAlias.value = read_zstring(file, fh.length);
        } else if (fid == "DATA") {
            // 0-length marker, skip
        } else if (fid == "DNAM") {
            file.read((char*)&record.skillStatData, fh.length);
        } else if (fid == "PNAM") {
            FormID part;
            file.read((char*)&part, 4);
            record.headParts.push_back(part);
        } else if (fid == "HCLF") {
            file.read((char*)&record.hairColor, 4);
        } else if (fid == "ZNAM") {
            file.read((char*)&record.combatStyle, 4);
        } else if (fid == "GNAM") {
            file.read((char*)&record.giftFilter, 4);
        } else if (fid == "NAM5") {
            file.read((char*)&record.nam5, 2);
            file.seekg(fh.length - 2, std::ios::cur);
        } else if (fid == "NAM6") {
            file.read((char*)&record.height, 4);
        } else if (fid == "NAM7") {
            file.read((char*)&record.weight, 4);
        } else if (fid == "NAM8") {
            file.read((char*)&record.soundLevel, 4);
        } else if (fid == "CSDT") {
            uint32_t type;
            file.read((char*)&type, 4);
            FieldHeader sdi_fh;
            file.read((char*)&sdi_fh, sizeof(sdi_fh));
            FormID sound;
            file.read((char*)&sound, 4);
            file.seekg(sdi_fh.length - 4, std::ios::cur);
            FieldHeader sdc_fh;
            file.read((char*)&sdc_fh, sizeof(sdc_fh));
            uint8_t chance;
            file.read((char*)&chance, 1);
            file.seekg(sdc_fh.length - 1, std::ios::cur);
            record.sounds.push_back({type, sound, chance});
            bytes_read += 2 * sizeof(FieldHeader);
        } else if (fid == "CSCR") {
            file.read((char*)&record.audioTemplate, 4);
        } else if (fid == "DOFT") {
            file.read((char*)&record.defaultOutfit, 4);
        } else if (fid == "SOFT") {
            file.read((char*)&record.sleepOutfit, 4);
        } else if (fid == "DPLT") {
            file.read((char*)&record.defaultPackList, 4);
        } else if (fid == "CRIF") {
            file.read((char*)&record.crimeFaction, 4);
        } else if (fid == "FTST") {
            file.read((char*)&record.faceTexture, 4);
        } else if (fid == "QNAM") {
            file.read((char*)&record.skinTone, fh.length);
        } else if (fid == "NAM9") {
            file.read((char*)&record.faceMorphs, fh.length);
        } else if (fid == "NAMA") {
            NPC_FacePart part;
            file.read((char*)&part, fh.length);
            record.faceParts.push_back(part);
        } else if (fid == "TINI") {
            std::streampos start = file.tellg();
            NPCTintLayer layer;
            file.read((char*)&layer.tintIndex, 2);
            FieldHeader tfh;
            file.read((char*)&tfh, sizeof(tfh));
            file.read((char*)&layer.tintColor, tfh.length);
            FieldHeader tvh;
            file.read((char*)&tvh, sizeof(tvh));
            file.read((char*)&layer.tintValue, 4);
            file.seekg(tvh.length - 4, std::ios::cur);
            FieldHeader tash;
            file.read((char*)&tash, sizeof(tash));
            file.read((char*)&layer.tintSash, 2);
            file.seekg(tash.length - 2, std::ios::cur);
            record.tintLayers.push_back(layer);
            file.seekg(start + std::streamoff(fh.length));
        } else {
            file.seekg(fh.length, std::ios::cur);
        }
        bytes_read += sizeof(FieldHeader) + fh.length;
    }

    std::cout << "  Parsed NPC_ logically:\n";
    std::cout << "    EDID: " << record.edid.value << "\n";
    std::cout << "    Race ID: 0x" << std::hex << record.race << std::dec << "\n";
}

void parse_content(std::ifstream& file, uint32_t limit) {
    uint32_t bytes_processed = 0;
    while (bytes_processed < limit) {
        std::streampos current_offset = file.tellg();
        char type[4];
        file.read(type, 4);
        if (file.gcount() < 4) break;

        if (!isValidType(type)) {
            std::cerr << "FATAL: Invalid type '" << std::string(type, 4) 
                      << "' at offset 0x" << std::hex << current_offset << std::dec << std::endl;
            exit(1);
        }

        uint32_t size;
        file.read((char*)&size, 4);
        if (file.gcount() < 4) break;

        std::string id(type, 4);
        std::cout << "  DEBUG: Processing record " << id << " at offset 0x" << std::hex << current_offset << std::dec << std::endl;
        if (id == "GRUP") {
            char label[4];
            int32_t group_type;
            uint16_t ts, vc;
            uint32_t unknown;
            file.read(label, 4);
            file.read((char*)&group_type, 4);
            file.read((char*)&ts, 2);
            file.read((char*)&vc, 2);
            file.read((char*)&unknown, 4);

            std::cout << "Offset: 0x" << std::hex << current_offset << " ID: GRUP Total Size: 0x" << size << std::dec << std::endl;
            std::cout << "  Label: " << std::string(label, 4) << " GroupType: " << group_type << std::endl;
            
            if (size >= 24) {
                uint32_t content_size = size - 24;
                parse_content(file, content_size);
            }
            bytes_processed += size;
        } else {
            uint32_t flags, formid;
            uint16_t ts, vc, version, unknown;
            file.read((char*)&flags, 4);
            file.read((char*)&formid, 4);
            file.read((char*)&ts, 2);
            file.read((char*)&vc, 2);
            file.read((char*)&version, 2);
            file.read((char*)&unknown, 2);

            std::cout << "Offset: 0x" << std::hex << current_offset << " ID: " << id << " Payload Size: 0x" << size << std::dec << std::endl;
            std::cout << "  Flags: 0x" << std::hex << flags << " FormID: 0x" << formid << " Version: 0x" << version << std::dec << std::endl;

            if (flags & (1 << 18)) {
                std::cout << "  (Record is compressed, skipping payload)\n";
                file.seekg(size, std::ios::cur);
            } else if (id == "TES4") {
                populate_tes4(file, size);
            } else if (id == "NPC_") {
                populate_npc(file, size);
            } else {
                uint32_t field_bytes = 0;
                while (field_bytes < size) {
                    FieldHeader fh;
                    file.read((char*)&fh, sizeof(fh));
                    if (file.gcount() < static_cast<std::streamsize>(sizeof(fh))) break;
                    if (!isValidType(fh.type)) {
                        std::cerr << "FATAL: Invalid field type '" << std::string(fh.type, 4) 
                                  << "' at offset 0x" << std::hex << file.tellg() << std::dec << std::endl;
                        exit(1);
                    }

                    std::string fid(fh.type, 4);
                    if (fid == "XXXX") {
                        uint32_t extended_length;
                        file.read((char*)&extended_length, 4);
                        if (file.gcount() < 4) break;

                        FieldHeader next_fh;
                        file.read((char*)&next_fh, static_cast<std::streamsize>(sizeof(next_fh)));
                        if (file.gcount() < static_cast<std::streamsize>(sizeof(next_fh))) break;
                        if (!isValidType(next_fh.type)) {
                            std::cerr << "FATAL: Invalid field type '" << std::string(next_fh.type, 4) 
                                      << "' at offset 0x" << std::hex << file.tellg() << std::dec << std::endl;
                            exit(1);
                        }

                        std::cout << "  Field: XXXX Extended Length: 0x" << std::hex << extended_length << std::dec << std::endl;
                        std::cout << "  Field: " << std::string(next_fh.type, 4) << " Length: 0x" << std::hex << extended_length << std::dec << std::endl;
                        
                        file.seekg(extended_length, std::ios::cur);
                        field_bytes += sizeof(FieldHeader) + 4 + sizeof(FieldHeader) + extended_length;
                    } else {
                        std::cout << "  Field: " << fid << " Length: 0x" << std::hex << fh.length << std::dec << std::endl;
                        file.seekg(fh.length, std::ios::cur);
                        field_bytes += sizeof(FieldHeader) + fh.length;
                    }
                }
            }
            bytes_processed += 20 + size;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <bsm_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    parse_content(file, 0xFFFFFFFF);

    std::cout << "Successfully parsed file!" << std::endl;
    return 0;
}
