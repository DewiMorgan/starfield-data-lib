#include "BPTD.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema BPTD::schema = {{
    FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->editorId.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"MODL", 0, -1, [](Record* r, Field* f) { std::memcpy(&static_cast<BPTD*>(r)->model.minX, f->raw_data.data(), std::min(static_cast<size_t>(24), f->raw_data.size())); }},
    GroupSchema{"part_group", 0, -1, {{
        FieldSchema{"BPTN", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().body_part_name.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"BPNN", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().body_part_node_name.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"BPNT", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().body_part_node_title.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"BPNI", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().body_part_node_info.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"BPND", 1, 1, [](Record* r, Field* f) { std::memcpy(static_cast<BPTD*>(r)->parts.back().bpnd, f->raw_data.data(), std::min(static_cast<size_t>(84), f->raw_data.size())); }},
        FieldSchema{"NAM1", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().limb_replacement_model.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"NAM4", 1, 1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().gore_effects.value = static_cast<ZStringField*>(f)->value; }},
        FieldSchema{"NAM5", 1, -1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->parts.back().hashes.emplace_back(*reinterpret_cast<const uint32*>(f->raw_data.data())); }}
    }}, 0, UNLIMITED},
    FieldSchema{"RAGA", 0, -1, [](Record* r, Field* f) { static_cast<BPTD*>(r)->ragdoll = *reinterpret_cast<const FormID*>(f->raw_data.data()); }}
}};

const RecordSchema& BPTD::getSchema() { return schema; }
