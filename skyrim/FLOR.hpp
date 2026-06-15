#ifndef FLOR_H
#define FLOR_H

struct FLOR {
    zstring editorId;
    VMAD scriptData;
    OBND objectBounds;
    lstring ingameName;
    MODL model;
    DEST destructionData;
    uint32 count;
    std::vector<formid> keywords;
    uint32 unknown;
    lstring verbString;
    uint16 flags;
    formid ingredient;
    formid pickupSound;
    uint32 percentChance;
};


#endif