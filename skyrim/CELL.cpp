#include "CELL.hpp"
#include <cstring>

const RecordSchema CELL::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<CELL*>(r)->edid.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) { static_cast<CELL*>(r)->full.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=2) std::memcpy(&static_cast<CELL*>(r)->data, f->raw_data.data(), 2); },},
        FieldSchema{"XCLC", 1, 1, [](Record* r, Field* f) { (void)r; (void)f; }},
        FieldSchema{"XCLL", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<CELL*>(r)->xcll, f->raw_data.data(), std::min((size_t)92,f->raw_data.size())); },},
        FieldSchema{"TVDT", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<CELL*>(r)->tvdt, f->raw_data.data(), std::min((size_t)684,f->raw_data.size())); },},
        FieldSchema{"MHDT", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<CELL*>(r)->mhdt, f->raw_data.data(), std::min((size_t)1028,f->raw_data.size())); },},
        FieldSchema{"XCGD", 1, 1, [](Record* r, Field* f) { (void)r; (void)f; }},
        FieldSchema{"LTMP", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->ltmp, f->raw_data.data(), 4); },},
        FieldSchema{"LNAM", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<CELL*>(r)->lnam, f->raw_data.data(), std::min((size_t)4,f->raw_data.size())); },},
        FieldSchema{"XCLW", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xclw, f->raw_data.data(), 4); },},
        FieldSchema{"XNAM", 1, 1, [](Record* r, Field* f) { if(!f->raw_data.empty()) static_cast<CELL*>(r)->xnam = f->raw_data[0]; },},
        FieldSchema{"XCLR", 1, 1, [](Record* r, Field* f) { (void)r; (void)f; }},
        FieldSchema{"XLCN", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xlcn, f->raw_data.data(), 4); },},
        FieldSchema{"XWCS", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xwcs, f->raw_data.data(), 4); },},
        FieldSchema{"XWCN", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xwcn, f->raw_data.data(), 4); },},
        FieldSchema{"XWCU", 1, 1, [](Record* r, Field* f) { (void)r; (void)f; }},
        FieldSchema{"XCWT", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xcwt, f->raw_data.data(), 4); },},
        FieldSchema{"XOWN", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xown, f->raw_data.data(), 4); },},
        FieldSchema{"XILL", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xill, f->raw_data.data(), 4); },},
        FieldSchema{"XWEM", 1, 1, [](Record* r, Field* f) { static_cast<CELL*>(r)->xwem.value = static_cast<ZStringField*>(f)->value; },},
        FieldSchema{"XCCM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xccm, f->raw_data.data(), 4); },},
        FieldSchema{"XCAS", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xcas, f->raw_data.data(), 4); },},
        FieldSchema{"XEZN", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xezn, f->raw_data.data(), 4); },},
        FieldSchema{"XCMO", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xcmo, f->raw_data.data(), 4); },},
        FieldSchema{"XCIM", 1, 1, [](Record* r, Field* f) { if(f->raw_data.size()>=4) std::memcpy(&static_cast<CELL*>(r)->xcim, f->raw_data.data(), 4); },},
    }
};
