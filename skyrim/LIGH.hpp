#ifndef LIGH_H
#define LIGH_H

struct LIGH {
    zstring editorId;
    VMAD scripting;
    OBND bounds;
    MODL model;
    DEST destructionData;
    lstring itemName;
    zstring icon;
    zstring messageIcon;
    LIGHData lightData;
    float fade;
    formid holdingSound;
};


#endif