#ifndef SPEL_H
#define SPEL_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "OBND.hpp"

struct SPEL {
    ZString edid;
    OBND obnd;
    lstring full;
    FormID mdob;
    FormID etyp;
    lstring desc;
    struct spit;
    FormID efid;
    struct efit;
    CTDA ctda;
};

#endif