#include "EYES.hpp"
#include <cstring>

const RecordSchema EYES::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<EYES*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"FULL", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<EYES*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->description.value = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        FieldSchema{"ICON", 0, 1, [](Record* r, Field* f) {
            static_cast<EYES*>(r)->path.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<EYES*>(r);
            memcpy(&rec->type, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->type));
        }},
    }
};
