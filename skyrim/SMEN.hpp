#ifndef SMEN_H
#define SMEN_H

#include "base_types.hpp"
#include "CHAR.hpp"
#include "CTDA.hpp"

struct SMEN {
    ZString edid;
    FormID pnam;
    FormID snam;
    uint32 citc;
    CTDA ctda;
    uint32 dnam;
    uint32 xnam;
    std::array<CHAR, 4> enam;
};

#endif