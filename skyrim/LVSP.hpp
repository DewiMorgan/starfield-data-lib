#ifndef LVSP_H
#define LVSP_H

#include "base_types.hpp"
#include "OBND.hpp"
#include <vector>

struct LVSPEntry {
    uint32 level;
    FormID spellId;
    uint32 count;
};

struct LVSP : public Record {
    ZString edid;
    OBND obnd;
    uint8 lvld = 0;
    uint8 lvlf = 0;
    uint8 llct = 0;
    std::vector<LVSPEntry> entries;

    static const RecordSchema schema;
};

#endif
