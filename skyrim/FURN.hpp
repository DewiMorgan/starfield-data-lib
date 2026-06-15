#ifndef FURN_H
#define FURN_H

#include "base_types.hpp"
#include <vector>

struct FURNMarker {
    uint32 markerIndex;
    uint32 nam0_flags;
    FormID fnmk_keyword;
    uint32 fnpr_flags;
};

struct FURN {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    lstring full;
    MODL modl;
    DEST dest;
    uint32 ksiz;
    std::vector<FormID> kwda;
    uint32 pnam;
    uint16 fnam;
    FormID knam;
    uint32 mnam;
    uint8 wbdt[2];
    MODL xmrk;
    FormID nam1;
    std::vector<FURNMarker> markers;
};

#endif
