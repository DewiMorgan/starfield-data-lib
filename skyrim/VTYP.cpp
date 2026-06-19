#include "VTYP.hpp"
#include "core.hpp"

const RecordSchema VTYP::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<VTYP*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"DNAM", 1, 1, [](Record* r, Field* f) { if (f->raw_data.size() >= 1) memcpy(&static_cast<VTYP*>(r)->type, f->raw_data.data(), sizeof(uint8)); }},
    }
};

const RecordSchema& VTYP::getSchema() const {
    return schema;
}
