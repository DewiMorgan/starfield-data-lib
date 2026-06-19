#include "ASPC.hpp"
#include "core.hpp"

const RecordSchema ASPC::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<ASPC*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"OBND", 1, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<ASPC*>(r)->objectBounds, f->raw_data.data(), std::min(static_cast<size_t>(sizeof(OBND)), f->raw_data.size())); }},
    FieldSchema{"SNAM", 0, -1, [](Record* r, Field* f) { static_cast<ASPC*>(r)->ambient = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"RDAT", 0, -1, [](Record* r, Field* f) { static_cast<ASPC*>(r)->regionData = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"BNAM", 0, -1, [](Record* r, Field* f) { static_cast<ASPC*>(r)->reverb = *reinterpret_cast<const FormID*>(f->raw_data.data()); }}
}};

