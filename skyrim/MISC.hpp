#ifndef MISC_H
#define MISC_H

struct MISC {
    zstring editorId;
    VMAD scriptInfo;
    OBND objectBounds;
    lstring name;
    MODL model;
    zstring inventoryImage;
    zstring messageImage;
    DEST destructionData;
    formid pickupSound;
    formid dropSound;
    uint32 keywordCount;
    std::vector<formid> keywords;
    MISCItemData itemData;
};


#endif