#include "DOBJ.hpp"
#include <cstring>

const RecordSchema DOBJ::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<DOBJ*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DNAM", 1, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<DOBJ*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            // DNAM contains pairs of (char[4] tag + FormID formid), 8 bytes each
            size_t count = raw.size() / sizeof(DOBJEntry);
            for (size_t i = 0; i < count; ++i) {
                DOBJEntry entry;
                memcpy(entry.tag, raw.data() + i * sizeof(DOBJEntry), 4);
                memcpy(&entry.formid, raw.data() + i * sizeof(DOBJEntry) + 4, sizeof(FormID));
                rec->entries.push_back(entry);
            }
        }},
    }
};
