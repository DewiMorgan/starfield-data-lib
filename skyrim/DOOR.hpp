#ifndef DOOR_H
#define DOOR_H

struct DOOR {
    zstring editorId;
    VMAD scriptData;
    OBND objectBounds;
    lstring fullName;
    MODL model;
    formid openSound;
    formid closeSound;
    formid loopSound;
    uint8 flags;
    std::vector<formid> randomTeleports;
};


#endif