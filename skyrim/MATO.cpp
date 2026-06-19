#include "MATO.hpp"
#include "core.hpp"
#include <cstring>
#include <algorithm>

const RecordSchema MATO::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<MATO*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"MODL", 0, 1, [](Record* r, Field* f) { static_cast<MATO*>(r)->modelPath.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) { static_cast<MATO*>(r)->propertyData.insert(static_cast<MATO*>(r)->propertyData.end(), static_cast<RawField*>(f)->raw_data.begin(), static_cast<RawField*>(f)->raw_data.end()); }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= sizeof(MATO::MaterialData)) memcpy(&static_cast<MATO*>(r)->data, static_cast<RawField*>(f)->raw_data.data(), sizeof(MATO::MaterialData)); }},
    }
};

const RecordSchema& MATO::getSchema() const { return schema; }

bool MATO::validate() {
    return true;
}
