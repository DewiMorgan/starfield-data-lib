#ifndef MATT_H
#define MATT_H

#include "base_types.hpp"

struct MATT {
    ZString edid;
    ZString mnam;
    FormID hnam;
    FormID pnam;
    std::array<float, 3> cnam;
    float bnam;
    uint32 fnam;
};

#endif