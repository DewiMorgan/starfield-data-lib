#ifndef IPDS_H
#define IPDS_H

#include "base_types.hpp"
#include <vector>

struct IPDSPair {
    FormID matt;
    FormID ipct;
};

struct IPDS {
    zstring editorId;
    std::vector<IPDSPair> pairs;
};

#endif
