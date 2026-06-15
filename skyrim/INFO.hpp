#ifndef INFO_H
#define INFO_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include <vector>
#include <string>

struct INFOResponse {
    uint32 emotionType;
    uint32 emotionValue;
    int32 unknown1;
    uint8 responseId;
    uint8 junk[3];
    FormID soundFile;
    uint8 useEmoAnim;
    uint8 junk2[3];
    ZString text;
    ZString notes;
    ZString edits;
    FormID speakerIdleAnims;
    FormID listenerIdleAnims;
    std::vector<CTDA> conditions;
};

struct INFO {
    ZString edid;
    VMAD vmad;
    uint16 dialogueTab;
    uint16 flags;
    float resetTime;
    FormID previousInfo;
    uint8 favorLevel;
    std::vector<FormID> topicLinks;
    FormID sharedInfo;
    std::vector<INFOResponse> responses;
    lstring playerResponse;
    FormID speaker;
    FormID walkAwayTopic;
    FormID audioOutputOverride;
};

#endif
