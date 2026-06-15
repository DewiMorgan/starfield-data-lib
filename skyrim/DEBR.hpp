#ifndef DEBR_H
#define DEBR_H

#include "base_types.hpp"
#include <vector>

struct DEBRData {
    uint8 percentage;
    ZString modelPath;
    uint8 flags;
};

struct DEBR {
    zstring editorId;
    std::vector<DEBRData> directionalData;
    std::vector<MODT> modelData;
};

#endif
