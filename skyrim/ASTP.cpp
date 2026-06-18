#include "ASTP.hpp"
#include <cstring>

const RecordSchema ASTP::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<ASTP*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"MPRT", 1, 1, [](Record* r, Field* f) { static_cast<ASTP*>(r)->maleParentLabel.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"FPRT", 1, 1, [](Record* r, Field* f) { static_cast<ASTP*>(r)->femaleParentLabel.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"MCHT", 0, 1, [](Record* r, Field* f) { static_cast<ASTP*>(r)->maleChildLabel.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"FCHT", 0, 1, [](Record* r, Field* f) { static_cast<ASTP*>(r)->femaleChildLabel.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<ASTP*>(r)->flags, f->raw_data.data(), 4); },},
    }
};
