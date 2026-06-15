#ifndef DIAL_H
#define DIAL_H

struct DIAL {
    zstring editorId;
    dlstring playerDialogue;
    float priority;
    formid owningBranch;
    formid owningQuest;
    DIALData data;
    char subtype[4];
    uint32 infoCount;
};


#endif