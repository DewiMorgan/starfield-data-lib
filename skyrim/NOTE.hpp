#ifndef NOTE_H
#define NOTE_H

#include "base_types.hpp"
#include "OBND.hpp"
#include "VMAD.hpp"

struct NOTE {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    MODL modl;
    lstring full;
    uint8 data;
    ZString icon;
    FormID onam;
    ZString xnam;
    FormID ynam;
    FormID znam;
    FormID snam;
    lstring tnam_l;
    FormID tnam_id;
};

#endif