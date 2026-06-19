#ifndef LVLI_H
#define LVLI_H

#include "base_types.hpp"
#include "OBND.hpp"
#include <vector>

struct LVLIEntry {
    uint32 level;
    FormID item;
    uint32 count;
};

struct LVLI : public Record {
    ZString edid;
    OBND obnd;
    int8 lvld = 0;
    int8 lvlf = 0;
    FormID lvlg = 0;
    int8 llct = 0;
    std::vector<LVLIEntry> entries;

    static const RecordSchema schema;
};

#endif
