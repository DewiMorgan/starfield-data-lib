#include "AVIF.hpp"
#include <cstring>

static std::string read_lstring(const std::vector<uint8_t>& data) {
    size_t end = data.size();
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == 0x1C) { end = i; break; }
    }
    return std::string(reinterpret_cast<const char*>(data.data()), end);
}

// Schema elements for a single PerkSection block
static const std::vector<SchemaElement> perkSectionFields = {
    FieldSchema{"PNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        if (rec->perkTree.empty()) {
            PerkSection empty = PerkSection{};
            rec->perkTree.push_back(empty);
        }
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.perk, raw->raw_data.data(), 4);
        }
    }},
    FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.flag, raw->raw_data.data(), 4);
        }
    }},
    FieldSchema{"XNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.x_coord, raw->raw_data.data(), 4);
        }
    }},
    FieldSchema{"YNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.y_coord, raw->raw_data.data(), 4);
        }
    }},
    FieldSchema{"HNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.h_pos, raw->raw_data.data(), sizeof(float));
        }
    }},
    FieldSchema{"VNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.v_pos, raw->raw_data.data(), sizeof(float));
        }
    }},
    FieldSchema{"SNAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.skill, raw->raw_data.data(), 4);
        }
    }},
    FieldSchema{"CNAM", 0, -1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        if (!rec->perkTree.empty()) {
            auto& section = rec->perkTree.back();
            auto* raw = static_cast<RawField*>(f);
            uint32 val = 0;
            if (raw->raw_data.size() >= 4) {
                std::memcpy(&val, raw->raw_data.data(), 4);
            }
            section.connecting_lines.push_back(val);
        }
    }},
    FieldSchema{"INAM", 1, 1, [](Record* r, Field* f) {
        AVIF* rec = static_cast<AVIF*>(r);
        auto& section = rec->perkTree.back();
        auto* raw = static_cast<RawField*>(f);
        if (raw->raw_data.size() >= 4) {
            std::memcpy(&section.index_number, raw->raw_data.data(), 4);
        }
    }}
};

const RecordSchema AVIF::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<AVIF*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"FULL", 0, 1, [](Record* r, Field* f) { static_cast<AVIF*>(r)->name.value = read_lstring(f->raw_data); }},
    FieldSchema{"DESC", 0, 1, [](Record* r, Field* f) { static_cast<AVIF*>(r)->description.value = read_lstring(f->raw_data); }},
    FieldSchema{"ANAM", 0, 1, [](Record* r, Field* f) { static_cast<AVIF*>(r)->abbreviation.value = static_cast<ZStringField*>(f)->value; }},
    GroupSchema{perkSectionFields, 0, -1},
}};
