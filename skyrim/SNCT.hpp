#ifndef SNCT_H
#define SNCT_H

struct SNCT {
    ZString editorId;
    lstring full_name;
    uint32 flags;
    FormID parent_name;
    uint16 static_volume_mult;
    uint16 default_menu_value;
};


#endif