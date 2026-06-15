#ifndef LVSP_H
#define LVSP_H

#include "base_types.hpp"
#include <vector>

struct LVSPEntry {
    uint32 level;
    FormID spellId;
    uint32 count;
};

struct LVSP {
    ZString edid;
    OBND obnd;
    uint8 lvld;
    uint8 lvlf;
    uint8 llct;
    std::vector<LVSPEntry> entries;
};

#endif
