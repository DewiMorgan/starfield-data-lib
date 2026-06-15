#ifndef CSTY_H
#define CSTY_H

struct CSTY {
    zstring editorId;
    std::vector<float> general;
    std::vector<float> melee;
    std::vector<float> closeRange;
    float longRange;
    std::vector<float> flight;
    uint32 flags;
};


#endif