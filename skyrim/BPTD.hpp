#ifndef BPTD_HPP
#define BPTD_HPP

#include "base_types.hpp"
#include "OBND.hpp"
#include "core.hpp"

struct BPTDPart {
    lstring body_part_name;
    zstring body_part_node_name;
    zstring body_part_node_title;
    zstring body_part_node_info;
    uint8 bpnd[84];
    zstring limb_replacement_model;
    zstring gore_effects;
    std::vector<uint32> hashes;
};

struct BPTD : public Record {
    zstring editorId;
    OBND model;
    std::vector<BPTDPart> parts;
    FormID ragdoll;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
