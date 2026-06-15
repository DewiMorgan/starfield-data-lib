#ifndef MODEL_H
#define MODEL_H

#pragma once

#include "base_types.hpp"
#include <array>
#include <vector>

struct MODEL {
    uint32 count;
    uint32 unknown4count;
    uint32 unknown5count;
    std::vector<uint32> unknown3;
    std::vector<uint32> unknown4;
    std::vector<uint32> unknown5;
    uint32 field_6;
    std::array<uint8, 4> texture_type;
    uint32 field_8;
    std::vector<uint32> field_9;
    uint32 field_10;
    std::array<uint8, 4> field_11;
    uint32 field_12;
};


#endif