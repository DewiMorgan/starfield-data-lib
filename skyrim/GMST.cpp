#include "GMST.hpp"
#include <cstring>

const RecordSchema GMST::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<GMST*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<GMST*>(r);
            rec->data = static_cast<RawField*>(f)->raw_data;
        }},
    }
};
