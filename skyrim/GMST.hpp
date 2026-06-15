#ifndef GMST_H
#define GMST_H

#include "base_types.hpp"
#include <vector>

struct GMST {
    ZString edid;
    std::vector<uint8> data;
};

#endif
