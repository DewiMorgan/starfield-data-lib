#include "CLMT.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema CLMT::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<CLMT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"WLST", 0, -1, [](Record* r, Field* f) { static_cast<CLMT*>(r)->wlstData.insert(static_cast<CLMT*>(r)->wlstData.end(), f->raw_data.begin(), f->raw_data.end()); }},
    FieldSchema{"FNAM", 0, -1, [](Record* r, Field* f) { static_cast<CLMT*>(r)->sunTexture.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"GNAM", 0, -1, [](Record* r, Field* f) { static_cast<CLMT*>(r)->glareTexture.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"MODL", 0, -1, [](Record* r, Field* f) { std::memcpy(&static_cast<CLMT*>(r)->nightSkyModel.minX, f->raw_data.data(), std::min(static_cast<size_t>(24), f->raw_data.size())); }},
    FieldSchema{"TNAM", 1, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<CLMT*>(r)->sunAndMoon, f->raw_data.data(), std::min(static_cast<size_t>(6), f->raw_data.size())); }}
}};

const RecordSchema& CLMT::getSchema() { return schema; }
