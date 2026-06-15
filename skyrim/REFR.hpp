#ifndef REFR_H
#define REFR_H

#include "base_types.hpp"
#include <vector>
#include <string>

struct XLRM {
    uint8 count;
    uint8 flags;
    uint8 padding[2];
    std::vector<FormID> rooms;
};

struct REFR {

    ZString edid;
    VMAD vmad;
    FormID name;
    float xmbo[3];
    XPRM xprm;
    FormID xpod[2];
    XLRM xrlm;
    FormID lnam;
    FormID inam;
    std::vector<FormID> xlrm;
    uint8 xrgd[128]; // long binary stream
    float xrds;
    FormID xemi;
    XLIG xlig;
    XESP xesp;
    uint8 xalp[2];
    XNDP xndp;
    XTEL xtel;
    float xscl;
    uint8 xapd;
    XPRM xapr; // approximation
    FormID xlib;
    std::vector<XLKR> xlkr;
    XLOC xloc;
    FormID xlrt;
    FormID xown;
    uint32 xcnt;
    float xcvl[3];
    float xcvr[3];
    uint8 xcza;
    uint8 xczc;
    FormID xezn;
    float xfvc;
    uint8 fnam;
    lstring full;
    uint16 tnam;
    uint8 xhtw;
    uint8 xis2;
    uint32 xlcm;
    FormID xmbr;
    uint8 xocp;
    FormID xpwr;
    uint32 xtri;
    uint8 onam;
    uint32 xact;
    FormID xatr;
    uint32 xwcn;
    std::vector<XWCU> xwcu;
    float xprd;
    uint8 xppa;
    uint8 pdto[8];
    FormID inam_pdto;
    FormID xlrl;
    float data[6];
};

#endif
