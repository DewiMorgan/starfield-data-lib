#ifndef DMDS_H
#define DMDS_H

#pragma once

#include "base_types.hpp"
#include <array>
#include <vector>

struct LIST;

struct DMDS {
    std::vector<LIST> Unknown;
    uint32 Number_of_entries;
    uint32 field_2;
    uint32 field_3;
    uint32 field_4;
    uint32 field_5;
};


#endif