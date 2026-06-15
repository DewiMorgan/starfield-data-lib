#ifndef TREE_H
#define TREE_H

struct TREE {
    ZString editorId;
    OBND objectBounds;
    MODL model;
    FormID result_item;
    FormID use_sound;
    uint8 percent_chance[4];
    lstring ingame_name;
    CNAM data;
};


#endif