#ifndef TACT_H
#define TACT_H

struct TACT {
    ZString editorId;
    VMAD unknown;
    OBND objectBounds;
    lstring full_name;
    MODL model;
    DEST destruction_data;
    uint32 keyword_count;
    std::vector<FormID> keywords;
    FormID looping_sound;
    FormID voice_type;
};


#endif