#ifndef CLAS_H
#define CLAS_H

#include "base_types.hpp"

struct CLAS {
    ZString edid;
    lstring full;
    lstring desc;
    ZString icon;
    uint8 data[36];
};

#endif