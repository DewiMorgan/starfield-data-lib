#include "CSTY.hpp"
#include <cstring>
#include <cmath>

const RecordSchema CSTY::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<CSTY*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"CSGD", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count; ++i) {
                float val;
                memcpy(&val, raw.data() + i * sizeof(float), sizeof(float));
                rec->general.push_back(val);
            }
        }},
        FieldSchema{"CSME", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count; ++i) {
                float val;
                memcpy(&val, raw.data() + i * sizeof(float), sizeof(float));
                rec->melee.push_back(val);
            }
        }},
        FieldSchema{"CSCR", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count; ++i) {
                float val;
                memcpy(&val, raw.data() + i * sizeof(float), sizeof(float));
                rec->closeRange.push_back(val);
            }
        }},
        FieldSchema{"CSLR", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            memcpy(&rec->longRange, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->longRange));
        }},
        FieldSchema{"CSFL", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count; ++i) {
                float val;
                memcpy(&val, raw.data() + i * sizeof(float), sizeof(float));
                rec->flight.push_back(val);
            }
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CSTY*>(r);
            memcpy(&rec->flags, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->flags));
        }},
    }
};
