#ifndef NVMI_H
#define NVMI_H

#pragma once

#include "base_types.hpp"
#include <array>
#include <vector>

struct NVMI {
    FormID Navmesh;
    uint32 Unknown;
    float X1;
    float Y1;
    float Z1;
    uint32 Preferred_Merges_Flag;
    uint32 Merged_to_Count;
    std::vector<FormID> Merged_to;
    uint32 Preferred_Merges_Count;
    std::vector<FormID> Preferred_Merges;
    uint8 Is_Island_Flag;
    uint32 Beginning_of_data_that_only_appears_if_the_Is_Island_Flag__TRUE;
    float X2;
    float Y2;
    float Z2;
    float X3;
    float Y3;
    float Z3;
    uint16 Vertex_index_0;
    uint16 Vertex_index_1;
    uint16 Vertex_index_2;
    float X4;
    float Y4;
    float Z4;
    uint32 End_of_data_that_only_appears_if_the_Is_Island_Flag__TRUE;
    uint32 Location_Marker;
    FormID World_Space;
    uint32 CellGrid;
};


#endif
