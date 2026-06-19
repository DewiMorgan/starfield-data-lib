#include "LGTM.hpp"
#include <cstring>

const RecordSchema LGTM::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LGTM*>(r);
            rec->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LGTM*>(r);
            // DATA is a complex struct: rgb+rgb+rgb+float+float+uint32+uint32+float+float+float+uint32x8+rgb+float+float+float+uint32
            // Total size = 4*3 (rgbs) + 4*3 (floats) + 4*2 (uint32s) + 4 (float) + 4 (float) + 4 (float) + 8*4 (unknown uint32s) + 4 (rgb) + 4 (float) + 4 (float) + 4 (float) + 4 (uint32) = 12+12+8+4+4+4+32+4+4+4+4+4 = 96 bytes
            memcpy(&rec->lighting, f->raw_data.data(), sizeof(LGTMLighting));
        }},
        FieldSchema{"DALC", 1, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LGTM*>(r);
            // DALC is: rgb x6 + float = 24 + 4 = 28 bytes
            memcpy(&rec->colors, f->raw_data.data(), sizeof(LGTMColors));
        }},
    }
};
