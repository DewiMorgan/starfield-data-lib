#include "REVB.hpp"
#include "core.hpp"

const RecordSchema REVB::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<REVB*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<REVB*>(r)->data, f->raw_data.data(), 14); }},
    }
};

const RecordSchema& REVB::getSchema() const {
    return schema;
}
