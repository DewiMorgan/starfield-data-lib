#ifndef CONT_H
#define CONT_H

#include "base_types.hpp"
#include <vector>

struct CONTObject {
    FormID item;
    uint32 count;
};

struct CONT {
    zstring editorId;
    VMAD scriptData;
    OBND objectBounds;
    lstring fullName;
    MODL model;
    uint32 objectCount;
    std::vector<CONTObject> containerObjects;
    std::vector<COED> coedData;
    CONTData data;
    FormID openSound;
    FormID closeSound;
};

#endif
