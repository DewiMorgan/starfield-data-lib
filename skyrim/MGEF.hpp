#ifndef MGEF_H
#define MGEF_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include <vector>
#include <string>

struct SNDDEntry {
    uint32 type;
    FormID soundDesc;
};

struct MGEF {
    ZString edid;
    VMAD vmad;
    lstring full;
    FormID mdob;
    uint32 ksiz;
    std::vector<FormID> kwda;
    uint8 data[152];
    std::vector<FormID> esce;
    std::vector<SNDDEntry> sndd;
    lstring dnam;
    CTDA ctda;
};

#endif
