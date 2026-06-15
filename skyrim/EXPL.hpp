#ifndef EXPL_H
#define EXPL_H

struct EXPL {
    zstring editorId;
    OBND objectBounds;
    lstring fullName;
    zstring model;
    std::vector<MODT> modelData;
    formid enchantment;
    formid modifier;
    EXPLData data;
};


#endif