#ifndef LCTN_H
#define LCTN_H

#include "base_types.hpp"

struct LCTN {
    ZString edid;
    std::vector<uint8> acpr_lcpr;
    std::vector<FormID> rcpr;
    std::vector<uint8> acun_lcun;
    std::vector<uint8> acsr_lcsr;
    uint8 acec_lcec;
    std::vector<uint8> acep_lcep;
    std::vector<FormID> acid_lcid;
    lstring full;
    KSIZ ksiz;
    KWDA kwda;
    FormID pnam;
    FormID nam1;
    FormID fnam;
    FormID mnam;
    float rnam;
    FormID nam0;
    rgb cnam;
};

#endif
