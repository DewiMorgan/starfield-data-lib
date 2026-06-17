#include "FSTS.hpp"
#include <cstring>

const RecordSchema FSTS::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FSTS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"XCNT", 1, 1, [](Record* r, Field* f) {
            std::memcpy(&static_cast<FSTS*>(r)->setCount, f->raw_data.data(), std::min((size_t)20, f->raw_data.size()));
        }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / sizeof(FormID);
            for (size_t i = 0; i < count; ++i) {
                FormID fid;
                std::memcpy(&fid, f->raw_data.data() + i * sizeof(FormID), sizeof(FormID));
                static_cast<FSTS*>(r)->footstepSets.push_back(fid);
            }
        }},
    }
};

void FSTS::populate(std::istream& is) {
    Record::populate(is);
}

bool FSTS::validate() {
    return Record::validate();
}
