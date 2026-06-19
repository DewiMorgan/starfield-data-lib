#include "MATT.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema MATT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<MATT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"MNAM", 1, 1, [](Record* r, Field* f) { static_cast<MATT*>(r)->materialName.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"HNAM", 0, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= 4) memcpy(&static_cast<MATT*>(r)->havokImpactData, static_cast<RawField*>(f)->raw_data.data(), 4); }},
        FieldSchema{"PNAM", 0, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= 4) memcpy(&static_cast<MATT*>(r)->parentMaterial, static_cast<RawField*>(f)->raw_data.data(), 4); }},
        FieldSchema{"CNAM", 1, 1, [](Record* r, Field* f) { auto raw = static_cast<RawField*>(f)->raw_data; memcpy(static_cast<MATT*>(r)->color.data(), raw.data(), std::min(raw.size(), sizeof(MATT::color))); }},
        FieldSchema{"BNAM", 1, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= sizeof(float)) memcpy(&static_cast<MATT*>(r)->buoyancy, static_cast<RawField*>(f)->raw_data.data(), sizeof(float)); }},
        FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= 4) memcpy(&static_cast<MATT*>(r)->flags, static_cast<RawField*>(f)->raw_data.data(), 4); }},
    }
};

const RecordSchema& MATT::getSchema() const { return schema; }

bool MATT::validate() {
    return true;
}
