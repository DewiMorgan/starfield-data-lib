#ifndef WTHR_H
#define WTHR_H

struct WTHR {
    ZString editorId;
    std::vector<ZString> cloud_textures;
    uint32 texture_layers;
    FormID precipitation;
    FormID visual_effect;
    std::vector<uint8> cloud_speed_y;
    std::vector<uint8> cloud_speed_x;
    std::vector<CloudTextureColor> cloud_texture_colors;
    std::vector<CloudTextureAlpha> cloud_texture_alphas;
    std::vector<ColorDefinition> color_definitions;
    FNAM fog_distance;
    DATA weather_data;
    uint32 disabled_flags;
    std::vector<AmbientSound> ambient_sounds;
    std::vector<FormID> sky_statics;
    FormID image_spaces[4];
    std::vector<LightingData> lighting_data;
    MODL aurora_model;
    uint32 unknown_nam2[4];
    uint32 unknown_nam3[4];
};


#endif