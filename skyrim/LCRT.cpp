#include "LCRT.hpp"
#include <cstring>

const RecordSchema LCRT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LCRT*>(r);
            rec->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"CNAM", 0, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LCRT*>(r);
            // CNAM is raw data (3 bytes rgb), copy into the struct
            memset(&rec->colorCode, 0, sizeof(rec->colorCode));
            uint8_t len = std::min(static_cast<uint8_t>(f->raw_data.size()), static_cast<uint8_t>(3));
            memcpy(&rec->colorCode, f->raw_data.data(), len);
        }},
    }
};
