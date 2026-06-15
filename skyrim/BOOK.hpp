#ifndef BOOK_H
#define BOOK_H

#include "base_types.hpp"
#include "DEST.hpp"
#include "OBND.hpp"
#include "VMAD.hpp"

struct BOOK {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    lstring full;
    MODL modl;
    ZString icon;
    ZString mico;
    lstring desc;
    DEST dest;
    FormID ynam;
    FormID znam;
    uint32 ksiz;
    std::vector<FormID> kwda;
    struct data;
    FormID inam;
    lstring cnam;
};

#endif