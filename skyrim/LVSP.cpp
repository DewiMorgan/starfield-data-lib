#include "LVSP.hpp"
#include <cstring>

const RecordSchema LVSP::schema = {
    {
        // EDID (+) - required zstring
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<LVSP*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        // OBND (+) - required 24 bytes
        FieldSchema{"OBND", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVSP*>(r)->obnd;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= 24) {
                memcpy(&rec.minX, raw.data(), 12);
                memcpy(&rec.maxX, raw.data() + 12, 12);
            }
        }},
        // LVLD (+) - required uint8
        FieldSchema{"LVLD", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVSP*>(r)->lvld;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LVLF (+) - required uint8
        FieldSchema{"LVLF", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVSP*>(r)->lvlf;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LLCT (+) - required uint8
        FieldSchema{"LLCT", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVSP*>(r)->llct;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LVLO (+) - repeating 12-byte chunk: level(uint32), spellId(FormID), count(uint32)
        FieldSchema{"LVLO", 1, -1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVSP*>(r);
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= 12) {
                LVSPEntry e{};
                memcpy(&e.level, raw.data(), sizeof(e.level));
                memcpy(&e.spellId, raw.data() + 4, sizeof(e.spellId));
                memcpy(&e.count, raw.data() + 8, sizeof(e.count));
                rec->entries.push_back(e);
            }
        }},
    }
};
