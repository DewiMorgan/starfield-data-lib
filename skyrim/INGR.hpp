#ifndef INGR_H
#define INGR_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "OBND.hpp"
#include "VMAD.hpp"

struct INGR {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    lstring full;
    uint32 ksiz;
    std::vector<FormID> kwda;
    MODL modl;
    ZString icon;
    FormID ynam;
    FormID znam;
    struct data;
    struct enit;
    FormID efid;
    struct efit;
    CTDA ctda;
};

#endif