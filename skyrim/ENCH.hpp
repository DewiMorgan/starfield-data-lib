#ifndef ENCH_H
#define ENCH_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "OBND.hpp"

struct ENCH {
    ZString edid;
    OBND obnd;
    lstring full;
    struct enit;
    FormID efid;
    struct efit;
    CTDA ctda;
};

#endif