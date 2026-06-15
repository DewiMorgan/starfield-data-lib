#ifndef KEYM_H
#define KEYM_H

#include "base_types.hpp"
#include <vector>
#include <string>

struct KEYMData {
    uint32 value;
    float weight;
};

struct KEYM {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    lstring full;
    ZString modl;
    std::vector<MODT> modt;
    FormID ynam;
    FormID znam;
    KSIZ ksiz;
    KWDA kwda;
    KEYMData data;
};

#endif
