#include "SNCT.hpp"
#include "core.hpp"

const RecordSchema SNCT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<SNCT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) { static_cast<SNCT*>(r)->fullName = std::string(reinterpret_cast<char*>(f->raw_data.data()), f->raw_data.size()); }},
        FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) { memcpy(&static_cast<SNCT*>(r)->flags, f->raw_data.data(), sizeof(uint32)); }},
        FieldSchema{"PNAM", 0, 1, [](Record* r, Field* f) { if (f->raw_data.size() >= 4) memcpy(&static_cast<SNCT*>(r)->parentName, f->raw_data.data(), 4); }},
        FieldSchema{"VNAM", 1, 1, [](Record* r, Field* f) { memcpy(&static_cast<SNCT*>(r)->staticVolumeMult, f->raw_data.data(), sizeof(uint16)); }},
        FieldSchema{"UNAM", 0, 1, [](Record* r, Field* f) { if (f->raw_data.size() >= 2) memcpy(&static_cast<SNCT*>(r)->defaultMenuValue, f->raw_data.data(), sizeof(uint16)); }},
    }
};

const RecordSchema& SNCT::getSchema() const {
    return schema;
}
