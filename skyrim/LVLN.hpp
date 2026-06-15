#ifndef LVLN_H
#define LVLN_H

#include "base_types.hpp"
#include <vector>

struct LVLNEntry {
    uint32 level;
    FormID npc;
    uint32 count;
};

struct LVLN {
    ZString edid;
    OBND obnd;
    uint8 lvld;
    uint8 lvlf;
    uint8 llct;
    std::vector<LVLNEntry> entries;
    MODL model;
};

#endif
