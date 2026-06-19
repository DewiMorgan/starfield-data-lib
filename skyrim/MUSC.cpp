#include "MUSC.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema MUSC::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<MUSC*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= 4) memcpy(&static_cast<MUSC*>(r)->flags, static_cast<RawField*>(f)->raw_data.data(), 4); }},
        FieldSchema{"PNAM", 1, 1, [](Record* r, Field* f) { const auto& raw = static_cast<RawField*>(f)->raw_data; if (raw.size() >= 4) memcpy(&static_cast<MUSC*>(r)->data, raw.data(), 4); }},
        FieldSchema{"WNAM", 1, 1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= sizeof(float)) memcpy(&static_cast<MUSC*>(r)->fadeDuration, static_cast<RawField*>(f)->raw_data.data(), sizeof(float)); }},
        FieldSchema{"TNAM", 0, -1, [](Record* r, Field* f) { if (static_cast<RawField*>(f)->raw_data.size() >= 4) { FormID formid; memcpy(&formid, static_cast<RawField*>(f)->raw_data.data(), 4); static_cast<MUSC*>(r)->musicTracks.push_back(formid); }}}
    }
};

const RecordSchema& MUSC::getSchema() const { return schema; }

bool MUSC::validate() {
    return true;
}
