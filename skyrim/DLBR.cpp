#include "DLBR.hpp"
#include <cstring>

const RecordSchema DLBR::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"QNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<DLBR*>(r);
            memcpy(&rec->qnam, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->qnam));
        }},
        FieldSchema{"TNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<DLBR*>(r);
            memcpy(&rec->tnam, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->tnam));
        }},
        FieldSchema{"DNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<DLBR*>(r);
            memcpy(&rec->dnam, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->dnam));
        }},
        FieldSchema{"SNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<DLBR*>(r);
            memcpy(&rec->snam, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->snam));
        }},
    }
};
