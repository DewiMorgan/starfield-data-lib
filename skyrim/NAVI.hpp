#ifndef NAVI_H
#define NAVI_H

struct NAVI {
    zstring editorId;
    uint32 version;
    std::vector<NVMI> navmeshData;
    NVPP navmeshPreferredPathing;
    std::vector<formid> unknownRefs;
};


#endif