#include "EFSH.hpp"
#include <cstring>

const RecordSchema EFSH::schema = {
    {
        FieldSchema{"EDID", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"ICON", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->startEffect.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"ICO2", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->loopedEffect.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"NAM7", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->postEffect.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"NAM8", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->loopedGradient.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"NAM9", 0, 1, [](Record* r, Field* f) {
            static_cast<EFSH*>(r)->endGradient.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            std::memcpy(&static_cast<EFSH*>(r)->data, f->raw_data.data(), std::min((size_t)400, f->raw_data.size()));
        }},
    }
};

void EFSH::populate(std::istream& is) {
    Record::populate(is);
}

bool EFSH::validate() {
    return Record::validate();
}
