#ifndef HAZD_H
#define HAZD_H

struct HAZD {
    zstring editorId;
    OBND objectBounds;
    lstring fullName;
    zstring model;
    MODT modelData;
    formid unknownFormId;
    HAZDData data;
};


#endif