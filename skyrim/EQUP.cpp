#include "EQUP.hpp"
#include <cstring>

const RecordSchema EQUP::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<EQUP*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"PNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<EQUP*>(r);
            formid fid;
            memcpy(&fid, static_cast<RawField*>(f)->raw_data.data(), sizeof(fid));
            rec->equipSlots.push_back(fid);
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<EQUP*>(r);
            uint8_t val;
            memcpy(&val, static_cast<RawField*>(f)->raw_data.data(), 1);
            rec->useAllParents = (val != 0);
        }},
    }
};
