#ifndef COBJ_H
#define COBJ_H

#include "base_types.hpp"
#include "COED.hpp"
#include "CTDA.hpp"

struct COBJ {
    ZString edid;
    uint32 coct;
    uint8 cnto[8];
    COED coed;
    CTDA ctda;
    FormID cnam;
    FormID bnam;
    uint16 NAM1;
};

#endif