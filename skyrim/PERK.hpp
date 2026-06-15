#ifndef PERK_H
#define PERK_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include <vector>
#include <string>

struct PERKSection {
    uint8 prke[3];
    uint8 prkc;
    std::vector<CTDA> conditions;
    uint8 epft;
    std::vector<uint8> epf_data;
    uint8 prkf;
};

struct PERK {
    ZString edid;
    VMAD vmad;
    lstring full;
    ZString desc;
    ZString icon;
    std::vector<CTDA> conditions;
    uint8 data[5];
    FormID nnam;
    std::vector<PERKSection> sections;
};

#endif
