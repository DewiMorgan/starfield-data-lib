#ifndef TXST_H
#define TXST_H

struct TXST {
    ZString editorId;
    uint8 objectBounds[12];
    std::vector<ZString> textures;
    DODT decalData;
    uint16 flags;
};


#endif