#include "MOVT.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema MOVT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<MOVT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"MNAM", 1, 1, [](Record* r, Field* f) { static_cast<MOVT*>(r)->name.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"SPED", 1, 1, [](Record* r, Field* f) { auto rec = static_cast<MOVT*>(r); const auto& raw = static_cast<RawField*>(f)->raw_data; rec->defaultData.insert(rec->defaultData.end(), raw.begin(), raw.end()); }},
        FieldSchema{"INAM", 0, 1, [](Record* r, Field* f) { auto rec = static_cast<MOVT*>(r); const auto& raw = static_cast<RawField*>(f)->raw_data; if (raw.size() >= 12) memcpy(rec->animThresholds, raw.data(), 12); }},
    }
};

const RecordSchema& MOVT::getSchema() const { return schema; }

bool MOVT::validate() {
    return true;
}
