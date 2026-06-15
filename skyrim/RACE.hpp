#ifndef RACE_H
#define RACE_H

#include "base_types.hpp"
#include "NPC_.hpp"
#include <vector>
#include <string>

struct FacialExpression {
    ZString phtn;
    float phwt[16];
};

struct RACE {
    ZString editorId;
    lstring full_name;
    lstring description;
    uint32 spell_count;
    std::vector<FormID> spells;
    FormID skin;
    BODT body_template;
    uint32 keyword_count;
    std::vector<FormID> keywords;
    DATA general_race_stats;

    ZString male_skeletal_model;
    MODT male_model_data;
    ZString female_skeletal_model;
    MODT female_model_data;

    char movement_type_name[4];
    FormID default_voice_types[2];
    FormID decapitate_armor[2];
    FormID default_hair_color[2];
    uint16 tint_index_number;
    float facegen_main_clamp;
    float facegen_face_clamp;
    FormID attack_race;

    std::vector<NPCAttackData> attack_data;

    ZString male_lighting_model;
    uint8_t male_lighting_model_texture_data[12];
    ZString female_lighting_model;
    uint8_t female_lighting_model_texture_data[12];

    FormID body_part_data;

    ZString male_physics_model;
    uint8_t male_physics_model_texture_data[12];
    ZString female_physics_model;
    uint8_t female_physics_model_texture_data[12];

    FormID material_type;
    FormID unarmed_impact_data_set;
    FormID decapitation_fx;
    FormID open_loot_sound;
    FormID close_loot_sound;

    std::vector<ZString> biped_object_names;
    FormID movement_override;
    SPED override_values;
    uint32 equipment_type_flags;
    FormID equip_slot;
    FormID unarmed_equip_slot;

    std::vector<FacialExpression> facial_expressions;

    FormID walk_movt;
    FormID run_movt;
    FormID swim_movt;
    FormID fly_movt;
    FormID sneak_movt;
    FormID sprint_movt;

    FormID morph_race;
    FormID armor_race;
};


#endif
