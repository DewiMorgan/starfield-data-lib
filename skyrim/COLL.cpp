#include "COLL.hpp"
#include <cstring>

const RecordSchema COLL::schema = {
    {
        FieldSchema{"EDID", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DESC", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->description.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"BNAM", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->uniqueId = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"FNAM", 0, 1, [](Record* r, Field* f) {
            std::memcpy(&static_cast<COLL*>(r)->debugColor, f->raw_data.data(), std::min((size_t)3, f->raw_data.size()));
        }},
        FieldSchema{"GNAM", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->flags = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"MNAM", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->name.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"INTV", 0, 1, [](Record* r, Field* f) {
            static_cast<COLL*>(r)->interactablesCount = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"CNAM", 0, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / sizeof(FormID);
            for (size_t i = 0; i < count; ++i) {
                FormID fid;
                std::memcpy(&fid, f->raw_data.data() + i * sizeof(FormID), sizeof(FormID));
                static_cast<COLL*>(r)->interactables.push_back(fid);
            }
        }},
    }
};

void COLL::populate(std::istream& is) {
    Record::populate(is);
}

bool COLL::validate() {
    return Record::validate();
}
