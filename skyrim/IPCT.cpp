#include "IPCT.hpp"
#include <cstring>

const RecordSchema IPCT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<IPCT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"MODL", 0, 1, [](Record* r, Field* f) { static_cast<IPCT*>(r)->model = std::string(reinterpret_cast<char*>(f->raw_data.data()), f->raw_data.size()); }},
        FieldSchema{"MODT", 0, 1, [](Record* r, Field* f) { uint8 raw[12]; std::memcpy(raw, f->raw_data.data(), std::min(f->raw_data.size(), sizeof(raw))); std::memcpy(&static_cast<IPCT*>(r)->modelTextures, raw, sizeof(MODT)); }},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<IPCT*>(r)->data, f->raw_data.data(), std::min(f->raw_data.size(), sizeof(IPCT::data))); }},
        FieldSchema{"DODT", 0, 1, [](Record* r, Field* f) { std::memcpy(static_cast<IPCT*>(r)->decalData, f->raw_data.data(), std::min(f->raw_data.size(), sizeof(IPCT::decalData))); }},
        FieldSchema{"DNAM", 0, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IPCT*>(r)->textureSet, f->raw_data.data(), sizeof(FormID)); }},
        FieldSchema{"ENAM", 0, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IPCT*>(r)->secondaryTextureSet, f->raw_data.data(), sizeof(FormID)); }},
        FieldSchema{"SNAM", 0, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IPCT*>(r)->impactSound1, f->raw_data.data(), sizeof(FormID)); }},
        FieldSchema{"NAM1", 0, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IPCT*>(r)->impactSound2, f->raw_data.data(), sizeof(FormID)); }},
        FieldSchema{"NAM2", 0, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<IPCT*>(r)->effectHazard, f->raw_data.data(), sizeof(FormID)); }},
    }
};
