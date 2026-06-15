#ifndef MUSC_H
#define MUSC_H

struct MUSC {
    zstring editorId;
    uint32 flags;
    MUSCData data;
    float fadeDuration;
    std::vector<formid> musicTracks;
};


#endif