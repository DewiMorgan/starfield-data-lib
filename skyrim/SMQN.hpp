#ifndef SMQN_H
#define SMQN_H

#include "base_types.hpp"
#include "CTDA.hpp"

struct SMQN {
    ZString edid;
    FormID pnam;
    FormID snam;
    uint32 citc;
    CTDA ctda;
    ZString CIS2;
    uint32 dnam;
    uint32 xnam;
    uint32 qnam;
    FormID nnam;
    float rnam;
};

#endif