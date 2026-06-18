#include "FSTS.hpp"
#include <cstring>

const RecordSchema FSTS::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FSTS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"XCNT", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FSTS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            size_t sz = std::min(sizeof(rec->setCount.value), raw.size());
            rec->setCount.value.assign(reinterpret_cast<const char*>(raw.data()), sz);
        }},
        FieldSchema{"DATA", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<FSTS*>(r);
            formid fid;
            memcpy(&fid, static_cast<RawField*>(f)->raw_data.data(), sizeof(fid));
            rec->footstepSets.push_back(fid);
        }},
    }
};
