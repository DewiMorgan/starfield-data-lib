#include "EFSH.hpp"
#include <cstring>

const RecordSchema EFSH::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<EFSH*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; },},
    }
};
