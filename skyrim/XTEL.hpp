#ifndef XTEL_H
#define XTEL_H
#include "base_types.hpp"
struct XTEL {
    FormID dest;
    float pos[3];
    float rot[3];
    uint32 flags;
};
#endif
