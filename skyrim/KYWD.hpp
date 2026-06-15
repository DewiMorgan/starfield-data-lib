#ifndef KYWD_H
#define KYWD_H

#include "base_types.hpp"

struct KYWD {
    ZString edid;
    rgb cnam;
    uint32 ksiz;
    std::vector<FormID> kwda;
};

#endif