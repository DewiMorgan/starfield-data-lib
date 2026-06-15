#ifndef MSTT_H
#define MSTT_H

struct MSTT {
    zstring editorId;
    OBND objectBounds;
    MODL model;
    DEST destructionData;
    uint8 flags;
    formid loopingSound;
};


#endif