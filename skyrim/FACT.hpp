#ifndef FACT_H
#define FACT_H

#include "base_types.hpp"
#include <vector>

struct FACT {
    ZString edid;
    lstring full;
    ZString desc;
    ZString icon;
    uint32 data;
    std::vector<uint8> crva;
    uint8 venv[12];
    uint8 plvd[12];
    FormID ynam;
    FormID znam;
};

#endif
