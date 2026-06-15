#ifndef SCRL_H
#define SCRL_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "DEST.hpp"
#include "MODL.hpp"
#include "OBND.hpp"

struct SCRL {
    ZString edid;
    OBND obnd;
    lstring full;
    uint32 ksiz;
    std::vector<FormID> kwda;
    FormID mdob;
    FormID etyp;
    lstring desc;
    MODL modl;
    FormID ynam;
    FormID znam;
    struct data;
    struct spit;
    DEST dest;
    FormID efid;
    struct efit;
    CTDA ctda;
};

#endif