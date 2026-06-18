#include "DIAL.hpp"
#include <cstring>

const RecordSchema DIAL::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<DIAL*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) { static_cast<DIAL*>(r)->playerDialogue.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"PNAM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<DIAL*>(r)->priority, f->raw_data.data(), 4); },},
        FieldSchema{"BNAM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<DIAL*>(r)->owningBranch, f->raw_data.data(), 4); },},
        FieldSchema{"QNAM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<DIAL*>(r)->owningQuest, f->raw_data.data(), 4); },},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<DIAL*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            size_t sz = std::min(sizeof(rec->data.value), raw.size());
            rec->data.value.assign(reinterpret_cast<const char*>(raw.data()), sz);
        }},
        FieldSchema{"SNAM", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<DIAL*>(r)->subtype, f->raw_data.data(), std::min((size_t)4,f->raw_data.size())); },},
        FieldSchema{"TIFC", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<DIAL*>(r)->infoCount, f->raw_data.data(), 4); },},
    }
};
