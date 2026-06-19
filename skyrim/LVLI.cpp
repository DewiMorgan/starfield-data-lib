#include "LVLI.hpp"
#include <cstring>

const RecordSchema LVLI::schema = {
    {
        // EDID (+) - required zstring
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<LVLI*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        // OBND (+) - required, use RawField to parse raw bytes into OBND struct
        FieldSchema{"OBND", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r)->obnd;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= 24) {
                memcpy(&rec.minX, raw.data(), 12);
                memcpy(&rec.maxX, raw.data() + 12, 12);
            }
        }},
        // LVLD (+) - required int8
        FieldSchema{"LVLD", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r)->lvld;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LVLF (+) - required int8
        FieldSchema{"LVLF", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r)->lvlf;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LVLG (-) - optional formID (uint32/4 bytes)
        FieldSchema{"LVLG", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r)->lvlg;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LLCT (-) - optional int8
        FieldSchema{"LLCT", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r)->llct;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // LVLO (*) - repeating 12-byte chunk: level(uint32), item(FormID), count(uint32)
        FieldSchema{"LVLO", 0, -1, [](Record* r, Field* f) {
            auto& rec = static_cast<LVLI*>(r);
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= 12) {
                LVLIEntry e{};
                memcpy(&e.level, raw.data(), sizeof(e.level));
                memcpy(&e.item, raw.data() + 4, sizeof(e.item));
                memcpy(&e.count, raw.data() + 8, sizeof(e.count));
                rec->entries.push_back(e);
            }
        }},
    }
};
