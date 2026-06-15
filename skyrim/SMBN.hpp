#ifndef SMBN_H
#define SMBN_H

#include "base_types.hpp"
#include "CTDA.hpp"

struct SMBN {
    ZString edid;
    FormID pnam;
    FormID snam;
    uint32 citc;
    CTDA ctda;
    ZString CIS2;
    uint32 dnam;
    uint32 xnam;
};

#endif