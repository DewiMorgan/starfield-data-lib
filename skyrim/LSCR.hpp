#ifndef LSCR_H
#define LSCR_H

#include "base_types.hpp"
#include "CTDA.hpp"

struct LSCR {
    ZString edid;
    lstring desc;
    CTDA ctda;
    FormID nnam;
    float snam;
    std::array<int16, 3> rnam;
    std::array<int16, 2> onam;
    std::array<float, 3> xnam;
    ZString MOD2;
};

#endif