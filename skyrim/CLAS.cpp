#include "CLAS.hpp"
#include <cstring>

const RecordSchema CLAS::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<CLAS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CLAS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            // lstring is delimited by 0x1C — find and remove it
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->full = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        FieldSchema{"DESC", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CLAS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->desc = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        FieldSchema{"ICON", 0, 1, [](Record* r, Field* f) {
            static_cast<CLAS*>(r)->icon.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CLAS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            memcpy(rec->data, raw.data(), std::min(sizeof(rec->data), raw.size()));
        }},
    }
};
