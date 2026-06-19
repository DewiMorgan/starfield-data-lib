#include "CPTH.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema CPTH::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"CTDA", 0, -1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->ctldaData.insert(static_cast<CPTH*>(r)->ctldaData.end(), f->raw_data.begin(), f->raw_data.end()); }},
    FieldSchema{"CIS1", 0, -1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->ctdaVariable.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"ANAM", 1, 1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->cameraPaths[0] = *reinterpret_cast<const FormID*>(f->raw_data.data()); std::memcpy(static_cast<CPTH*>(r)->cameraPaths + 1, f->raw_data.data() + 4, 4); }},
    FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->flags = *f->raw_data.data(); }},
    FieldSchema{"SNAM", 0, -1, [](Record* r, Field* f) { static_cast<CPTH*>(r)->cameras.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }}
}};

const RecordSchema& CPTH::getSchema() { return schema; }
