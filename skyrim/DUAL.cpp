#include "DUAL.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema DUAL::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<DUAL*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"OBND", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<DUAL*>(r)->objectBounds.minX, f->raw_data.data(), std::min(static_cast<size_t>(24), f->raw_data.size())); }},
    FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<DUAL*>(r)->dataRaw, f->raw_data.data(), std::min(static_cast<size_t>(24), f->raw_data.size())); }}
}};

const RecordSchema& DUAL::getSchema() { return schema; }
