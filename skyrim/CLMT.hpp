#ifndef CLMT_H
#define CLMT_H

#include "base_types.hpp"
#include <vector>

struct CLMTWeather {
    FormID wthr;
    uint32 chance;
    FormID global;
};

struct CLMT {
    zstring editorId;
    std::vector<CLMTWeather> weatherList;
    zstring sunTexture;
    zstring glareTexture;
    MODL nightSkyModel;
    CLMTSunMoon sunAndMoon;
};

#endif
