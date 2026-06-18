#include "FLST.hpp"
#include <cstring>

const RecordSchema FLST::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FLST*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"LNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<FLST*>(r);
            formid fid;
            memcpy(&fid, static_cast<RawField*>(f)->raw_data.data(), sizeof(fid));
            rec->objects.push_back(fid);
        }},
    }
};
