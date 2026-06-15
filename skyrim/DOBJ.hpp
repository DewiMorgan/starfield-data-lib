#ifndef DOBJ_H
#define DOBJ_H

#include "base_types.hpp"
#include <vector>

struct DOBJEntry {
    char tag[4];
    FormID formid;
};

struct DOBJ {
    zstring editorId;
    std::vector<DOBJEntry> entries;
};

#endif
