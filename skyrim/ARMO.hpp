#ifndef ARMO_H
#define ARMO_H

#include "base_types.hpp"
#include "BODT.hpp"
#include "DEST.hpp"
#include "OBND.hpp"
#include "VMAD.hpp"

struct ARMO {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    lstring full;
    FormID eitm;
    uint16 eamt;
    MODL modl;
    ZString MOD2;
    struct MO2T;
    MO2S alternate_textures_2;
    ZString icon;
    ZString mico;
    ZString MOD4;
    struct MO4T;
    MO4S alternate_textures_4;
    ZString ICO2;
    ZString MIC2;
    BODT bodt;
    BOD2 bod2;
    DEST dest;
    FormID ynam;
    FormID znam;
    ZString bmct;
    FormID etyp;
    FormID bids;
    FormID bamt;
    FormID rnam;
    uint32 ksiz;
    std::vector<FormID> kwda;
    lstring desc;
    FormID modl_id;
    struct data;
    uint32 dnam;
    FormID tnam;
};

#endif
