#ifndef DLBR_H
#define DLBR_H

#include "base_types.hpp"

struct DLBR {
    ZString edid;
    FormID qnam;
    uint32 tnam;
    uint32 dnam;
    FormID snam;
};

#endif