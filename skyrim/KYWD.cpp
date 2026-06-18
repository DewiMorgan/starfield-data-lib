#include "KYWD.hpp"
#include <cstring>

const RecordSchema KYWD::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<KYWD*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"CNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<KYWD*>(r);
            auto* raw = static_cast<RawField*>(f);
            // CNAM is an RGB color: read r, g, b from the first 3 bytes
            if (raw->raw_data.size() >= 3) {
                std::memcpy(&rec->color.r, raw->raw_data.data(), 3);
                rec->color.a = 0; // Alpha not stored in 3-byte CNAM
            } else {
                std::memset(&rec->color, 0, sizeof(rec->color));
            }
        }},
    }
};
