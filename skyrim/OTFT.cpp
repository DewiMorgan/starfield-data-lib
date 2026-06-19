#include "OTFT.hpp"

const RecordSchema OTFT::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<OTFT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) { static_cast<OTFT*>(r)->inventoryList.push_back(0); auto raw = reinterpret_cast<const FormID*>(f->raw_data.data()); memcpy(&const_cast<FormID&>(static_cast<OTFT*>(r)->inventoryList.back()), raw, sizeof(FormID)); }},
}};

const RecordSchema& OTFT::getSchema() const { return schema; }

bool OTFT::validate() {
    return !editorId.value.empty();
}
