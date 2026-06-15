#ifndef FSTS_H
#define FSTS_H

struct FSTS {
    zstring editorId;
    FSTSSetCount setCount;
    std::vector<formid> footstepSets;
};


#endif