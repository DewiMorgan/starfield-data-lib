#ifndef LAND_H
#define LAND_H

#include "base_types.hpp"

struct LAND {
    FormID atxt;
    FormID btxt;
    uint8 data[4];
    uint8 vclr[3267];
    uint8 vhgt[1096];
    uint8 vnml[3267];
    uint8 vtxt[8];
};

#endif
