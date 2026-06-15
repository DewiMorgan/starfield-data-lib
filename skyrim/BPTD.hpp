#ifndef BPTD_H
#define BPTD_H

#include "base_types.hpp"
#include <vector>
#include <string>

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

struct BPTD {
    zstring editorId;
    MODL model;
    std::vector<BPTDPart> parts;
    FormID ragdoll;
};

#endif
