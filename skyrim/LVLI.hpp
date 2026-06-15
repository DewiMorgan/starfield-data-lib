#ifndef LVLI_H
#define LVLI_H

#include "base_types.hpp"
#include <vector>

struct LVLIEntry {
    uint32 level;
    FormID item;
    uint32 count;
};

struct LVLI {
    ZString edid;
    OBND obnd;
    int8 lvld;
    int8 lvlf;
    FormID lvlg;
    int8 llct;
    std::vector<LVLIEntry> entries;
};

#endif
