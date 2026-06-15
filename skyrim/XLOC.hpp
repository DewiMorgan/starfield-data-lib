#ifndef XLOC_H
#define XLOC_H
#include "base_types.hpp"
struct XLOC {
    int8 level;
    uint8 flags[3];
    FormID keym;
    uint8 l_flags;
    uint8 padding[3];
    uint8 unused[8];
};
#endif
