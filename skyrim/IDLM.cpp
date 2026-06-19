#include "IDLM.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema IDLM::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<IDLM*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"OBND", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<IDLM*>(r)->objectBounds.minX, f->raw_data.data(), std::min(static_cast<size_t>(24), f->raw_data.size())); }},
    FieldSchema{"IDLF", 0, -1, [](Record* r, Field* f) { static_cast<IDLM*>(r)->flags = *f->raw_data.data(); }},
    FieldSchema{"IDLC", 0, -1, [](Record* r, Field* f) { static_cast<IDLM*>(r)->idleCount = *f->raw_data.data(); }},
    FieldSchema{"IDLT", 0, -1, [](Record* r, Field* f) { std::memcpy(&static_cast<IDLM*>(r)->idleTimer, f->raw_data.data(), sizeof(float)); }},
    FieldSchema{"IDLA", 0, -1, [](Record* r, Field* f) { static_cast<IDLM*>(r)->idleAnimations.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }}
}};

const RecordSchema& IDLM::getSchema() { return schema; }
