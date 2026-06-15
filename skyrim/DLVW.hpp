#ifndef DLVW_H
#define DLVW_H

#include "base_types.hpp"
#include "BYTE.hpp"

struct DLVW {
    ZString edid;
    FormID qnam;
    FormID bnam;
    FormID tnam;
    uint32 enam;
    BYTE dnam;
};

#endif