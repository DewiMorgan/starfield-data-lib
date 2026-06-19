#include "IDLE.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema IDLE::schema = {{
    FieldSchema{"EDID", 0, -1, [](Record* r, Field* f) { static_cast<IDLE*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"CTDA", 0, -1, [](Record* r, Field* f) { static_cast<IDLE*>(r)->scriptDataRaw.insert(static_cast<IDLE*>(r)->scriptDataRaw.end(), f->raw_data.begin(), f->raw_data.end()); }},
    FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) { static_cast<IDLE*>(r)->havokFile.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"ENAM", 0, -1, [](Record* r, Field* f) { static_cast<IDLE*>(r)->animEvent.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"ANAM", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<IDLE*>(r)->animations, f->raw_data.data(), std::min(static_cast<size_t>(8), f->raw_data.size())); }},
    FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IDLE*>(r)->data, f->raw_data.data(), std::min(static_cast<size_t>(6), f->raw_data.size())); }}
}};

const RecordSchema& IDLE::getSchema() { return schema; }
