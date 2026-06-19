#include "LTEX.hpp"
#include <cstring>
#include <algorithm>

const RecordSchema LTEX::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<LTEX*>(r)->edid.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"TNAM", 0, 1, [](Record* r, Field* f) { auto* raw = static_cast<RawField*>(f); if (raw->raw_data.size() >= 4) std::memcpy(&static_cast<LTEX*>(r)->tnam, raw->raw_data.data(), 4); }},
        FieldSchema{"MNAM", 1, 1, [](Record* r, Field* f) { auto* raw = static_cast<RawField*>(f); if (raw->raw_data.size() >= 4) std::memcpy(&static_cast<LTEX*>(r)->mnam, raw->raw_data.data(), 4); }},
        FieldSchema{"HNAM", 1, 1, [](Record* r, Field* f) { auto* raw = static_cast<RawField*>(f); std::memcpy(static_cast<LTEX*>(r)->hnam.data(), raw->raw_data.data(), std::min(raw->raw_data.size(), sizeof(LTEX::hnam))); }},
        FieldSchema{"SNAM", 1, 1, [](Record* r, Field* f) { auto* raw = static_cast<RawField*>(f); if (raw->raw_data.size() >= 1) static_cast<LTEX*>(r)->snam = raw->raw_data[0]; }},
        FieldSchema{"GNAM", 0, -1, [](Record* r, Field* f) { auto* raw = static_cast<RawField*>(f); if (raw->raw_data.size() >= 4) { FormID formid; std::memcpy(&formid, raw->raw_data.data(), 4); static_cast<LTEX*>(r)->gras.push_back(formid); }}},
    }
};

const RecordSchema& LTEX::getSchema() const { return schema; }
