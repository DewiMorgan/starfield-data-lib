#include "HDPT.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema HDPT::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"FULL", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->name.value = std::string(reinterpret_cast<const char*>(f->raw_data.data()), f->raw_data.size()); }},
    FieldSchema{"MODL", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->model.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"MODT", 0, -1, [](Record* r, Field* f) { std::memcpy(static_cast<HDPT*>(r)->modelTextureData, f->raw_data.data(), std::min(static_cast<size_t>(12), f->raw_data.size())); }},
    FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->flags = *f->raw_data.data(); }},
    FieldSchema{"PNAM", 1, 1, [](Record* r, Field* f) { std::memcpy(&static_cast<HDPT*>(r)->type, f->raw_data.data(), sizeof(uint32)); }},
    FieldSchema{"HNAM", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->additionalParts.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }},
    FieldSchema{"NAM0", 0, -1, [](Record* r, Field* f) { HDPTOption opt{}; std::memcpy(&opt.optionType, f->raw_data.data(), sizeof(uint32)); static_cast<HDPT*>(r)->options.push_back(opt); }},
    FieldSchema{"NM1", 0, -1, [](Record* r, Field* f) { if (!static_cast<HDPT*>(r)->options.empty()) static_cast<HDPT*>(r)->options.back().triFile.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"TNAM", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->baseTexture = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"RNAM", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->resourceList = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"CNAM", 0, -1, [](Record* r, Field* f) { static_cast<HDPT*>(r)->color = *reinterpret_cast<const FormID*>(f->raw_data.data()); }}
}};

const RecordSchema& HDPT::getSchema() { return schema; }
