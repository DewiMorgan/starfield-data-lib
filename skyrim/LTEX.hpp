#ifndef LTEX_H
#define LTEX_H

#include "base_types.hpp"

struct LTEX {
    ZString edid;
    FormID tnam;
    FormID mnam;
    std::array<uint8, 2> hnam;
    uint8 snam;
    FormID gnam;
};

#endif