#ifndef ALCH_H
#define ALCH_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "OBND.hpp"

struct ALCH {
    ZString edid;
    OBND obnd;
    lstring full;
    uint32 ksiz;
    std::vector<FormID> kwda;
    MODL modl;
    ZString icon;
    ZString mico;
    FormID ynam;
    FormID znam;
    float data;
    struct enit;
    FormID efid;
    struct efit;
    CTDA ctda;
};

#endif