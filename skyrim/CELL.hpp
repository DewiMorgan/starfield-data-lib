#ifndef CELL_H
#define CELL_H

#include "base_types.hpp"
#include <vector>

struct CELL {
    ZString edid;
    lstring full;
    uint16 data;
    uint8 xclc;
    uint8 xcll;
    uint8 tvdt[684];
    uint8 mhdt[1028];
    uint8 xcgd;
    FormID ltmp;
    uint8 lnam[4];
    float xclw;
    uint8 xnam;
    std::vector<FormID> xclr;
    FormID xlcn;
    uint32 xwcs;
    uint32 xwcn;
    std::vector<uint8> xwcu;
    FormID xcwt;
    FormID xown;
    FormID xill;
    ZString xwem;
    FormID xccm;
    FormID xcas;
    FormID xezn;
    FormID xcmo;
    FormID xcim;
};

#endif
