#ifndef CAMS_H
#define CAMS_H

struct CAMS {
    zstring editorId;
    zstring model;
    uint8 modelData[12];
    CamData camData;
    formid effect;
};


#endif