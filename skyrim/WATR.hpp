#ifndef WATR_H
#define WATR_H

struct WATR {
    ZString editorId;
    lstring unknown_full;
    uint8 opacity;
    uint8 flags;
    uint8 unknown_mnam;
    FormID spell_effect;
    FormID open_sound;
    FormID imagespace_modifier;
    FormID material;
    uint16 damage_per_second;
    DNAM data;
    uint8 unknown_gnam[12];
    float linear_velocity[3];
    float angular_velocity[3];
    ZString noise_texture_1;
    ZString noise_texture_2;
    ZString noise_texture_3;
};


#endif