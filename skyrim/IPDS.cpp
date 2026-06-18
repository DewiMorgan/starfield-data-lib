#include "IPDS.hpp"
#include <cstring>

const RecordSchema IPDS::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<IPDS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"PNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IPDS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= 8) {
                IPDSPair pair;
                memcpy(&pair.matt, raw.data(), sizeof(FormID));
                memcpy(&pair.ipct, raw.data() + 4, sizeof(FormID));
                rec->pairs.push_back(pair);
            }
        }},
    }
};
