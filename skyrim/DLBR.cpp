#include "DLBR.hpp"
#include <cstring>

const RecordSchema DLBR::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"QNAM", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->qnam = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"TNAM", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->tnam = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"DNAM", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->dnam = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"SNAM", 1, 1, [](Record* r, Field* f) {
            static_cast<DLBR*>(r)->snam = static_cast<NumericField<FormID>*>(f)->value;
        }},
    }
};

void DLBR::populate(std::istream& is) {
    Record::populate(is);
}

bool DLBR::validate() {
    return Record::validate();
}
