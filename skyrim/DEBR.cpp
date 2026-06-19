#include "DEBR.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema DEBR::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<DEBR*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"DATA", 0, -1, [](Record* r, Field* f) {
        DEBRData d{};
        if (f->raw_data.size() >= 2) {
            std::memcpy(&d.percentage, f->raw_data.data(), 1);
            // Find zstring end: scan from byte 1 for null terminator
            const uint8* start = f->raw_data.data() + 1;
            const uint8* end = std::search(start, f->raw_data.data() + f->raw_data.size() - 1, 
                                           static_cast<const uint8*>(static_cast<const void*>("\0")), static_cast<const uint8*>(static_cast<const void*>("\0") + 1));
            if (end != f->raw_data.data() + f->raw_data.size() - 1) {
                d.modelPath.value = std::string(reinterpret_cast<const char*>(start), end - start);
                // Last byte is flags
                uint8_t flags;
                std::memcpy(&flags, f->raw_data.data() + f->raw_data.size() - 1, 1);
                d.flags = flags;
            }
        }
        static_cast<DEBR*>(r)->directionalData.push_back(d);
    }},
    FieldSchema{"MODT", 0, -1, [](Record* r, Field* f) {
        static_cast<DEBR*>(r)->modelDataRaw.insert(static_cast<DEBR*>(r)->modelDataRaw.end(), f->raw_data.begin(), f->raw_data.end());
    }}
}};

const RecordSchema& DEBR::getSchema() { return schema; }
