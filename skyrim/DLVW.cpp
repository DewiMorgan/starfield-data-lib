#include "DLVW.hpp"
#include "core.hpp"

const RecordSchema DLVW::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<DLVW*>(r)->edid.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"QNAM", 1, 1, [](Record* r, Field* f) { static_cast<DLVW*>(r)->qnam = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"BNAM", 0, -1, [](Record* r, Field* f) { static_cast<DLVW*>(r)->bnam.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }},
    FieldSchema{"TNAM", 0, -1, [](Record* r, Field* f) { static_cast<DLVW*>(r)->tnam.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }},
    FieldSchema{"ENAM", 0, -1, [](Record* r, Field* f) { std::memcpy(&static_cast<DLVW*>(r)->enam, f->raw_data.data(), sizeof(uint32)); }},
    FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) { static_cast<DLVW*>(r)->dnam = *f->raw_data.data(); }}
}};

const RecordSchema& DLVW::getSchema() { return schema; }
