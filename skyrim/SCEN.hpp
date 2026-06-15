#ifndef SCEN_H
#define SCEN_H

#include "base_types.hpp"
#include "SCHR.hpp"
#include <vector>
#include <array>

struct SCEN_Phase {
    uint8 hnam_start; // marker
    ZString nam0;
    std::vector<uint8> start_conditions; // Simplified CTDA
    uint8 next_marker;
    std::vector<uint8> completion_conditions; // Simplified CTDA
    SCHR schr1;
    uint8 next_marker2;
    SCHR schr2;
    uint32 wnam;
    uint8 hnam_end; // marker
};

struct SCEN_Actor {
    uint32 alid;
    uint32 lnam;
    uint32 dnam;
};

struct SCEN_Action {
    uint16 anam;
    ZString nam0;
    uint32 alid;
    uint32 inam;
    uint32 fnam;
    uint32 snam_start;
    uint32 enam;
    // Dialogue only
    FormID data;
    int32 htid;
    float dmax;
    float dmin;
    uint32 demo;
    uint32 deva;
    // Package only
    FormID pnam;
    // Timer only
    float snam_duration;
    SCHR schr;
};

struct SCEN {
    ZString edid;
    std::vector<uint8> vmad;
    uint32 fnam;
    std::vector<SCEN_Phase> phases;
    std::vector<SCEN_Actor> actors;
    std::vector<SCEN_Action> actions;
    SCHR schr;
    FormID pnam;
    uint32 inam;
    std::array<uint32, 4> vnam;
    uint8 ctda; // Simplified
};

#endif
