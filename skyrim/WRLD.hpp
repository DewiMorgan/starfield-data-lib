#ifndef WRLD_H
#define WRLD_H

#include "base_types.hpp"
#include "MODL.hpp"

struct WRLD {
    ZString edid;
    struct rnam;
    std::vector<uint8> mhdt;
    lstring full;
    std::array<int16, 2> wctr;
    FormID ltmp;
    FormID xezn;
    FormID xlcn;
    FormID cnam;
    FormID NAM2;
    FormID NAM3;
    float NAM4;
    std::array<float, 2> dnam;
    MODL modl;
    struct mnam;
    float nama;
    uint8 data;
    std::array<int32, 2> NAM0;
    std::array<int32, 2> NAM9;
    FormID wnam;
    uint16 pnam;
    std::array<float, 4> onam;
    ZString tnam;
    ZString unam;
    FormID znam;
    ZString xwem;
    std::array<int32, 4> ofst;
};

#endif