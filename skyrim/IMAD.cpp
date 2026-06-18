#include "IMAD.hpp"
#include <cstring>

const RecordSchema IMAD::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<IMAD*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; },},
    }
};
