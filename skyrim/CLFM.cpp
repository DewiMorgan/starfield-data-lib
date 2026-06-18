#include "CLFM.hpp"
#include <cstring>

const RecordSchema CLFM::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<CLFM*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) { static_cast<CLFM*>(r)->full.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"CNAM", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<CLFM*>(r);
            auto* raw = static_cast<RawField*>(f);
            if (raw->raw_data.size() >= 3) {
                std::memcpy(&rec->cnam.r, raw->raw_data.data(), 3);
                rec->cnam.a = 0;
            } else {
                std::memset(&rec->cnam, 0, sizeof(rec->cnam));
            }
        }},
        FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CLFM*>(r)->fnam, f->raw_data.data(), 4); },},
    }
};
