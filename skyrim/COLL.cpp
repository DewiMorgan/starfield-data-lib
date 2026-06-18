#include "COLL.hpp"
#include <cstring>

const RecordSchema COLL::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DESC", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->description.value = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        FieldSchema{"BNAM", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            memcpy(&rec->uniqueId, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->uniqueId));
        }},
        FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            memcpy(&rec->debugColor.r, raw.data(), std::min(sizeof(rec->debugColor), raw.size()));
        }},
        FieldSchema{"GNAM", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            memcpy(&rec->flags, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->flags));
        }},
        FieldSchema{"MNAM", 1, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->name.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"INTV", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            memcpy(&rec->interactablesCount, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->interactablesCount));
        }},
        FieldSchema{"CNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<COLL*>(r);
            formid fid;
            memcpy(&fid, static_cast<RawField*>(f)->raw_data.data(), sizeof(fid));
            rec->interactables.push_back(fid);
        }},
    }
};
