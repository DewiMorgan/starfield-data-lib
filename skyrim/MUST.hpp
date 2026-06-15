#ifndef MUST_H
#define MUST_H

struct MUST {
    zstring editorId;
    uint32 trackType;
    float duration;
    float fadeOut;
    zstring trackA;
    zstring trackB;
    std::vector<float> cuePoints;
    std::vector<formid> tracks;
    MUSTLoopData loopData;
    uint32 conditionCount;
    std::vector<CTDA> conditions;
};


#endif