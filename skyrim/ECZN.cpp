#include "ECZN.hpp"
#include <cstring>

const RecordSchema ECZN::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<ECZN*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<ECZN*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            memcpy(rec->data, raw.data(), std::min(sizeof(rec->data), raw.size()));
        }},
    }
};
