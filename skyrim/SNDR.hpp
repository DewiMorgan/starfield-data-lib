#ifndef SNDR_H
#define SNDR_H

struct SNDR {
    ZString editorId;
    uint32 sound_descriptor_type;
    FormID category;
    FormID sound;
    uint32 unknown;
    std::vector<ZString> tracks;
    FormID output_model;
    std::vector<CTDA> condition_data;
    LNAM lnam;
    BNAM bnam;
};


#endif