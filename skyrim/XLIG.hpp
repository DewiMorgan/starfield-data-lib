#ifndef XLIG_H
#define XLIG_H
#include "base_types.hpp"
struct XLIG {
    float fov_offset;
    float fade_offset;
    float end_dist;
    float shadow_bias;
    uint8 padding[4];
};
#endif
