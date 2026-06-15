#ifndef REGN_H
#define REGN_H

#include "base_types.hpp"
#include <vector>

struct RPLD_Entry {
    uint8 data[8];
};

struct RDAT {
    uint32 tab;
    uint8 flags;
    uint8 priority;
    uint16 padding;
};

struct RDSA_Entry {
    FormID sound;
    uint32 flags;
    float chance;
};

struct RDWT_Entry {
    FormID weather;
    uint32 chance;
    FormID global;
};

struct RDOT_Entry {
    FormID object;
    int16 parent_index;
    uint16 unknown_1;
    float density;
    uint8 clustering;
    uint8 min_slope;
    uint8 max_slope;
    uint8 flags;
    uint16 radius_parent;
    uint16 radius;
    float min_height;
    float max_height;
    float sink;
    float sink_variance;
    float size_variance;
    int16 angle_var[3];
    uint16 unknown_2;
    uint8 color[3];
    uint8 shading_radius;
};

struct REGN {
    ZString edid;
    rgb rclr;
    FormID wnam;
    uint32 rpli;
    std::vector<RPLD_Entry> rpld;
    RDAT rdat;
    FormID rdmo;
    std::vector<RDSA_Entry> rdsa;
    std::vector<RDWT_Entry> rdwt;
    std::vector<RDOT_Entry> rdot;
    ZString icon;
    lstring rdmp;
};

#endif
