#ifndef COLL_H
#define COLL_H

struct COLL {
    zstring editorId;
    lstring description;
    uint32 uniqueId;
    rgb debugColor;
    uint32 flags;
    zstring name;
    uint32 interactablesCount;
    std::vector<formid> interactables;
};


#endif