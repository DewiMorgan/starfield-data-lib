#ifndef AVIF_H
#define AVIF_H

#include "base_types.hpp"
#include <vector>

struct PerkSection {
    FormID perk;
    uint32 flag;
    uint32 x_coord;
    uint32 y_coord;
    float h_pos;
    float v_pos;
    FormID skill;
    std::vector<uint32> connecting_lines;
    uint32 index_number;
};

struct AVIF {
    zstring editorId;
    lstring name;
    lstring description;
    zstring abbreviation;
    uint32 data;
    float avData[4];
    std::vector<PerkSection> perkTree;
};

#endif
