#ifndef PROJ_H
#define PROJ_H

struct PROJ {
    ZString editorID;
    OBND object_bounds;
    lstring full_name;
    MODL model;
    DEST destruction_data;
    MODL effect_model;
    DATA unknown;
    uint32 sound_detection_level;
};


#endif