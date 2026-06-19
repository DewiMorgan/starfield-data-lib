#include "WOOP.hpp"
#include <cstring>

const RecordSchema WOOP::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<WOOP*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) { static_cast<WOOP*>(r)->name.value = std::string(static_cast<RawField*>(f)->raw_data.begin(), static_cast<RawField*>(f)->raw_data.end()); }},
        FieldSchema{"TNAM", 1, 1, [](Record* r, Field* f) { static_cast<WOOP*>(r)->translation.value = std::string(static_cast<RawField*>(f)->raw_data.begin(), static_cast<RawField*>(f)->raw_data.end()); }},
    }
};

const RecordSchema& WOOP::getSchema() const {
    return schema;
}

bool WOOP::validate() {
    return true;
}
