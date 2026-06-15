#ifndef IDLM_H
#define IDLM_H

struct IDLM {
    zstring editorId;
    OBND objectBounds;
    uint8 flags;
    uint8 idleCount;
    float idleTimer;
    std::vector<formid> idleAnimations;
};


#endif