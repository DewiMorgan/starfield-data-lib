#ifndef CPTH_H
#define CPTH_H

struct CPTH {
    zstring editorId;
    std::vector<CTDA> conditions;
    zstring ctdaVariable;
    formid unknown[2];
    uint8 flags;
    std::vector<formid> cameras;
};


#endif