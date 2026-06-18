#include "CAMS.hpp"
#include <cstring>

const RecordSchema CAMS::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<CAMS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"MODL", 0, 1, [](Record* r, Field* f) { static_cast<CAMS*>(r)->model.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"MODT", 0, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=12) std::memcpy(static_cast<CAMS*>(r)->modelData, f->raw_data.data(), 12); }},
    FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { 
        std::string& data = static_cast<CAMS*>(r)->camData.value;
        data.assign(reinterpret_cast<const char*>(f->raw_data.data()), f->raw_data.size());
    }},
    FieldSchema{"MNAM", 0, 1, [](Record* r, Field* f) { 
        if(f->raw_data.size()>=4) std::memcpy(&static_cast<CAMS*>(r)->effect, f->raw_data.data(), 4); 
    }},
}};
