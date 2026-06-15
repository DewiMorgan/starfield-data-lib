#ifndef IPCT_H
#define IPCT_H

struct IPCT {
    zstring editorId;
    zstring model;
    MODT modelTextures;
    IPCTData data;
    IPCTDecalData decalData;
    formid textureSet;
    formid secondaryTextureSet;
    formid impactSound1;
    formid impactSound2;
    formid effectHazard;
};


#endif