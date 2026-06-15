#ifndef IDLE_H
#define IDLE_H

struct IDLE {
    zstring editorId;
    std::vector<CTDA> script;
    zstring havokFile;
    zstring animEvent;
    formid animations[2];
    IDLEData data;
};


#endif