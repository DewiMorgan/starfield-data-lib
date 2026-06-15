#ifndef WEAP_H
#define WEAP_H

#include "base_types.hpp"
#include "OBND.hpp"
#include "VMAD.hpp"

struct WEAP {
    FormID bamt;
    FormID bids;
    FormID cnam;
    struct crdt;
    std::array<uint8, 10> data;
    lstring desc;
    std::array<uint8, 100> dnam;
    uint16 eamt;
    ZString edid;
    FormID eitm;
    FormID etyp;
    lstring full;
    FormID inam;
    uint32 ksiz;
    std::vector<FormID> kwda;
    OBND obnd;
    ZString modl;
    std::vector<uint8> mods;
    std::vector<uint8> modt;
    FormID NAM7;
    FormID NAM8;
    FormID NAM9;
    ZString nnam;
    FormID snam;
    FormID tnam;
    FormID unam;
    VMAD vmad;
    uint32 vnam;
    FormID wnam;
    FormID xnam;
    FormID ynam;
    FormID znam;
};

#endif