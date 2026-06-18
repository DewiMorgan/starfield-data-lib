#include "FSTP.hpp"
#include <cstring>

const RecordSchema FSTP::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FSTP*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FSTP*>(r);
            memcpy(&rec->impactData, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->impactData));
        }},
        FieldSchema{"ANAM", 0, 1, [](Record* r, Field* f) {
            static_cast<FSTP*>(r)->actionName.value = static_cast<ZStringField*>(f)->value;
        }},
    }
};
