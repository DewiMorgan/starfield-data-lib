#ifndef SLGM_H
#define SLGM_H

#include "base_types.hpp"
#include "KSIZ.hpp"
#include "KWDA.hpp"
#include "OBND.hpp"

struct SLGM {
    ZString edid;
    OBND obnd;
    lstring full;
    ZString modl;
    std::vector<uint8> modt;
    KSIZ ksiz;
    KWDA kwda;
    uint8 soul;
    struct data;
    uint8 slcp;
    FormID NAM0;
    FormID znam;
};

#endif