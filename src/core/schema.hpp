#ifndef SCHEMA_H
#define SCHEMA_H

#include <string>
#include <vector>
#include <map>

enum class FieldType {
    String,
    Int32,
    Float,
    FormID,
    Unknown
};

struct TagInfo {
    std::string label;
    FieldType type;
};

struct RecordSchema {
    std::string label;
    std::map<std::string, TagInfo> tags;
};

// Global schema mapping Record Signatures (e.g., "WEAP") to their metadata
inline std::map<std::string, RecordSchema> g_RecordSchemas = {
    {"AACT", {"'Action'", {
        {"DNAM", {"DNAM", FieldType::String}},
        {"ENAM", {"ENAM", FieldType::String}}
    }}},
    {"AAMD", {"'Aim Assist Model Data'", {
        {"Inner Cone Angle Degrees", {"Inner Cone Angle Degrees", FieldType::Float}},
        {"Outer Cone Angle Degrees", {"Outer Cone Angle Degrees", FieldType::Float}},
        {"Steering Degrees Per Sec", {"Steering Degrees Per Sec", FieldType::Float}},
        {"Pitch Scale", {"Pitch Scale", FieldType::Float}},
        {"Inner Steering Ring", {"Inner Steering Ring", FieldType::Float}},
        {"Outer Steering Ring", {"Outer Steering Ring", FieldType::Float}},
        {"Friction", {"Friction", FieldType::Float}},
        {"Move Follow Degrees Per Sec", {"Move Follow Degrees Per Sec", FieldType::Float}},
        {"ADS Snap Steering Mult", {"ADS Snap Steering Mult", FieldType::Float}},
        {"ADS Snap Seconds", {"ADS Snap Seconds", FieldType::Float}},
        {"ADS Snap Cone Angle Degrees", {"ADS Snap Cone Angle Degrees", FieldType::Float}},
        {"No Steering", {"No Steering", FieldType::Float}},
        {"Bullet Bending Cone Angle Degrees", {"Bullet Bending Cone Angle Degrees", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Inner Ring", {"ADS Snap Steering Mutliplier Inner Ring", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Outer Ring", {"ADS Snap Steering Mutliplier Outer Ring", FieldType::Float}},
        {"ADS Multiplier Inner Cone Angle Degrees", {"ADS Multiplier Inner Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Outer Cone Angle Degrees", {"ADS Multiplier Outer Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Inner Steering Ring", {"ADS Multiplier Inner Steering Ring", FieldType::Float}},
        {"ADS Multiplier Outer Steering Ring", {"ADS Multiplier Outer Steering Ring", FieldType::Float}},
        {"ADS Multiplier Friction", {"ADS Multiplier Friction", FieldType::Float}},
        {"ADS Multiplier Steering Degrees Per Sec", {"ADS Multiplier Steering Degrees Per Sec", FieldType::Float}}
    }}},
    {"AAPD", {"'Aim Assist Pose Data'", {
        {"ANAM", {"ANAM", FieldType::String}},
        {"BNAM", {"BNAM", FieldType::String}},
        {"RADR", {"RADR", FieldType::Float}},
        {"WTMX", {"WTMX", FieldType::Float}}
    }}},
    {"ACTI", {"'Activator'", {
        {"WMAT", {"WMAT", FieldType::String}},
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}}
    }}},
    {"ADDN", {"'Addon Node'", {
        {"Master Particle System Cap", {"Master Particle System Cap", FieldType::Int32}}
    }}},
    {"AFFE", {"'Affinity Event'", {

    }}},
    {"AIDT", {"AI Data", {
        {"Energy Level", {"Energy Level", FieldType::Int32}}
    }}},
    {"ALCH", {"'Ingestible'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Addiction Chance", {"Addiction Chance", FieldType::Float}}
    }}},
    {"AMBS", {"'Ambience Set'", {
        {"Interval (Seonds", {"Interval (Seonds", FieldType::Float}}
    }}},
    {"AMDL", {"'Aim Model'", {
        {"Cone of Fire - Degrees X", {"Cone of Fire - Degrees X", FieldType::Float}},
        {"Cone of Fire - Degrees Y", {"Cone of Fire - Degrees Y", FieldType::Float}},
        {"Cone of Fire - Increase Per Shot", {"Cone of Fire - Increase Per Shot", FieldType::Float}},
        {"Cone of Fire - Decrease Per Sec", {"Cone of Fire - Decrease Per Sec", FieldType::Float}},
        {"Cone of Fire - Decrease Delay in Sec", {"Cone of Fire - Decrease Delay in Sec", FieldType::Float}},
        {"Cone of Fire - Sneak Mult", {"Cone of Fire - Sneak Mult", FieldType::Float}},
        {"Recoil - Diminish Spring Force", {"Recoil - Diminish Spring Force", FieldType::Float}},
        {"Recoil - Diminish Sights Mult", {"Recoil - Diminish Sights Mult", FieldType::Float}},
        {"Recoil - Degrees Per Shot X", {"Recoil - Degrees Per Shot X", FieldType::Float}},
        {"Recoil - Degrees Per Shot Y", {"Recoil - Degrees Per Shot Y", FieldType::Float}},
        {"Recoil - Hip Mult", {"Recoil - Hip Mult", FieldType::Float}},
        {"Recoil - Shots for Runaway", {"Recoil - Shots for Runaway", FieldType::Int32}},
        {"Recoil - Arc", {"Recoil - Arc", FieldType::Float}},
        {"Recoil - Arc Rotate", {"Recoil - Arc Rotate", FieldType::Float}},
        {"Cone of Fire - Iron Sights Mult", {"Cone of Fire - Iron Sights Mult", FieldType::Float}},
        {"Recoil - Base Stability", {"Recoil - Base Stability", FieldType::Float}}
    }}},
    {"AMMO", {"'Ammunition'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"Damage", {"Damage", FieldType::Float}},
        {"Health", {"Health", FieldType::Int32}},
        {"NAM1", {"NAM1", FieldType::String}}
    }}},
    {"ANAM", {"Data", {
        {"Cone of Fire - Degrees X", {"Cone of Fire - Degrees X", FieldType::Float}},
        {"Cone of Fire - Degrees Y", {"Cone of Fire - Degrees Y", FieldType::Float}},
        {"Cone of Fire - Increase Per Shot", {"Cone of Fire - Increase Per Shot", FieldType::Float}},
        {"Cone of Fire - Decrease Per Sec", {"Cone of Fire - Decrease Per Sec", FieldType::Float}},
        {"Cone of Fire - Decrease Delay in Sec", {"Cone of Fire - Decrease Delay in Sec", FieldType::Float}},
        {"Cone of Fire - Sneak Mult", {"Cone of Fire - Sneak Mult", FieldType::Float}},
        {"Recoil - Diminish Spring Force", {"Recoil - Diminish Spring Force", FieldType::Float}},
        {"Recoil - Diminish Sights Mult", {"Recoil - Diminish Sights Mult", FieldType::Float}},
        {"Recoil - Degrees Per Shot X", {"Recoil - Degrees Per Shot X", FieldType::Float}},
        {"Recoil - Degrees Per Shot Y", {"Recoil - Degrees Per Shot Y", FieldType::Float}},
        {"Recoil - Hip Mult", {"Recoil - Hip Mult", FieldType::Float}},
        {"Recoil - Shots for Runaway", {"Recoil - Shots for Runaway", FieldType::Int32}},
        {"Recoil - Arc", {"Recoil - Arc", FieldType::Float}},
        {"Recoil - Arc Rotate", {"Recoil - Arc Rotate", FieldType::Float}},
        {"Cone of Fire - Iron Sights Mult", {"Cone of Fire - Iron Sights Mult", FieldType::Float}},
        {"Recoil - Base Stability", {"Recoil - Base Stability", FieldType::Float}}
    }}},
    {"ANIO", {"'Animated Object'", {

    }}},
    {"AOPF", {"'Audio Occlusion Primitive'", {
        {"OBSV", {"OBSV", FieldType::Float}},
        {"OCCV", {"OCCV", FieldType::Float}}
    }}},
    {"AOPS", {"'Aim Optical Sight Marker'", {
        {"Delay Before Sight Activation", {"Delay Before Sight Activation", FieldType::Float}},
        {"Delay Before Sight Deactivation", {"Delay Before Sight Deactivation", FieldType::Float}},
        {"Focal Point Distance", {"Focal Point Distance", FieldType::Float}},
        {"Focal Point Distance During Aiming", {"Focal Point Distance During Aiming", FieldType::Float}},
        {"Delay Between Shots", {"Delay Between Shots", FieldType::Float}},
        {"Max Laser Pointer Distance", {"Max Laser Pointer Distance", FieldType::Float}}
    }}},
    {"AOR2", {"Data", {
        {"Radius", {"Radius", FieldType::Float}},
        {"Min Delay", {"Min Delay", FieldType::Float}},
        {"Max Delay", {"Max Delay", FieldType::Float}}
    }}},
    {"AORU", {"'Attraction Rule'", {
        {"Radius", {"Radius", FieldType::Float}},
        {"Min Delay", {"Min Delay", FieldType::Float}},
        {"Max Delay", {"Max Delay", FieldType::Float}}
    }}},
    {"ARMA", {"'Armor Addon'", {
        {"Weapon Adjust", {"Weapon Adjust", FieldType::Float}},
        {"Male Priority", {"Male Priority", FieldType::Int32}},
        {"Female Priority", {"Female Priority", FieldType::Int32}},
        {"Unknown", {"Unknown", FieldType::Int32}},
        {"Detection Sound Value", {"Detection Sound Value", FieldType::Int32}},
        {"Health Bar Offset", {"Health Bar Offset", FieldType::Float}},
        {"MOD6", {"MOD6", FieldType::String}},
        {"MOD7", {"MOD7", FieldType::String}},
        {"TNAM", {"TNAM", FieldType::String}},
        {"SNAM", {"SNAM", FieldType::String}},
        {"VNAM", {"VNAM", FieldType::String}}
    }}},
    {"ARMO", {"'Armor'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"Health", {"Health", FieldType::Int32}},
        {"Armor Rating", {"Armor Rating", FieldType::Int32}},
        {"Base Addon Index", {"Base Addon Index", FieldType::Int32}}
    }}},
    {"ARTO", {"'Art Object'", {

    }}},
    {"ASPC", {"'Acoustic Space'", {
        {"AEAR", {"AEAR", FieldType::Float}},
        {"FLTV", {"FLTV", FieldType::Float}}
    }}},
    {"ASTP", {"'Association Type'", {
        {"MPRT", {"MPRT", FieldType::String}},
        {"FPRT", {"FPRT", FieldType::String}},
        {"MCHT", {"MCHT", FieldType::String}},
        {"FCHT", {"FCHT", FieldType::String}}
    }}},
    {"ATKD", {"Attack Data", {
        {"Damage Mult", {"Damage Mult", FieldType::Float}},
        {"Attack Chance", {"Attack Chance", FieldType::Float}}
    }}},
    {"ATMO", {"'Atmosphere'", {

    }}},
    {"AVIF", {"'Actor Value Information'", {
        {"NAM0", {"NAM0", FieldType::Float}}
    }}},
    {"AVMD", {"'AVMS Data'", {
        {"YNAM", {"YNAM", FieldType::String}},
        {"TNAM", {"TNAM", FieldType::String}},
        {"LNAM", {"LNAM", FieldType::String}},
        {"VNAM", {"VNAM", FieldType::String}}
    }}},
    {"BDFS", {"Distant View", {
        {"Texture Offset U", {"Texture Offset U", FieldType::Float}},
        {"Texture Offset V", {"Texture Offset V", FieldType::Float}},
        {"Texture Scale U", {"Texture Scale U", FieldType::Float}},
        {"Texture Scale V", {"Texture Scale V", FieldType::Float}},
        {"Normal Strength", {"Normal Strength", FieldType::Float}},
        {"Slope Start", {"Slope Start", FieldType::Float}},
        {"Slope Range", {"Slope Range", FieldType::Float}},
        {"EFSD", {"EFSD", FieldType::String}}
    }}},
    {"BIOM", {"'Biome'", {
        {"SNAM", {"SNAM", FieldType::String}},
        {"Object Density", {"Object Density", FieldType::Float}},
        {"Giant", {"Giant", FieldType::Float}},
        {"Large", {"Large", FieldType::Float}},
        {"Medium", {"Medium", FieldType::Float}},
        {"Small", {"Small", FieldType::Float}},
        {"JNAM", {"JNAM", FieldType::String}},
        {"WNAM", {"WNAM", FieldType::Float}},
        {"YNAM", {"YNAM", FieldType::Float}},
        {"UNAM", {"UNAM", FieldType::Float}},
        {"TX00", {"TX00", FieldType::String}},
        {"UX00", {"UX00", FieldType::String}},
        {"VX00", {"VX00", FieldType::String}},
        {"WX00", {"WX00", FieldType::String}},
        {"XX00", {"XX00", FieldType::String}},
        {"YX00", {"YX00", FieldType::String}},
        {"TX16", {"TX16", FieldType::String}},
        {"Texture Offset U", {"Texture Offset U", FieldType::Float}},
        {"Texture Offset V", {"Texture Offset V", FieldType::Float}},
        {"Texture Scale U", {"Texture Scale U", FieldType::Float}},
        {"Texture Scale V", {"Texture Scale V", FieldType::Float}},
        {"Normal Strength", {"Normal Strength", FieldType::Float}},
        {"Slope Start", {"Slope Start", FieldType::Float}},
        {"Slope Range", {"Slope Range", FieldType::Float}},
        {"EFSD", {"EFSD", FieldType::String}},
        {"Interval (Seonds", {"Interval (Seonds", FieldType::Float}},
        {"Delay Before Sight Activation", {"Delay Before Sight Activation", FieldType::Float}},
        {"Delay Before Sight Deactivation", {"Delay Before Sight Deactivation", FieldType::Float}},
        {"Focal Point Distance", {"Focal Point Distance", FieldType::Float}},
        {"Focal Point Distance During Aiming", {"Focal Point Distance During Aiming", FieldType::Float}},
        {"Delay Between Shots", {"Delay Between Shots", FieldType::Float}},
        {"Max Laser Pointer Distance", {"Max Laser Pointer Distance", FieldType::Float}},
        {"TNAM", {"TNAM", FieldType::String}},
        {"LNAM", {"LNAM", FieldType::String}},
        {"VNAM", {"VNAM", FieldType::String}},
        {"Max Anim Distance", {"Max Anim Distance", FieldType::Float}},
        {"Inner", {"Inner", FieldType::Float}},
        {"Outer", {"Outer", FieldType::Float}},
        {"TMPP", {"TMPP", FieldType::String}},
        {"TCMP", {"TCMP", FieldType::String}},
        {"BMPP", {"BMPP", FieldType::String}},
        {"Base Vertex Color", {"Base Vertex Color", FieldType::Int32}},
        {"KNAM", {"KNAM", FieldType::FormID}},
        {"Chance", {"Chance", FieldType::Float}},
        {"Entry Size", {"Entry Size", FieldType::Int32}},
        {"Frequency", {"Frequency", FieldType::Int32}},
        {"GNAM", {"GNAM", FieldType::Float}},
        {"XEMP", {"XEMP", FieldType::String}},
        {"Axial Tilt", {"Axial Tilt", FieldType::Float}},
        {"Rotational Velocity", {"Rotational Velocity", FieldType::Float}},
        {"Mass (in Earth Masses", {"Mass (in Earth Masses", FieldType::Float}},
        {"Radius in km", {"Radius in km", FieldType::Float}},
        {"Surface Gravity", {"Surface Gravity", FieldType::Float}},
        {"Parent Planet ID", {"Parent Planet ID", FieldType::Int32}},
        {"Planet ID", {"Planet ID", FieldType::Int32}},
        {"Density", {"Density", FieldType::Float}},
        {"Heat", {"Heat", FieldType::Float}},
        {"Hydro", {"Hydro", FieldType::Float}},
        {"Inner HZ", {"Inner HZ", FieldType::Float}},
        {"Outer HZ", {"Outer HZ", FieldType::Float}},
        {"Peri. Angle", {"Peri. Angle", FieldType::Float}},
        {"Start angle in deg", {"Start angle in deg", FieldType::Float}},
        {"Year length in days", {"Year length in days", FieldType::Float}},
        {"Asteroids", {"Asteroids", FieldType::Int32}},
        {"Random Seed", {"Random Seed", FieldType::Int32}},
        {"Avg Density Frac.", {"Avg Density Frac.", FieldType::Float}},
        {"Rayleight Scattering Coefficient", {"Rayleight Scattering Coefficient", FieldType::Float}},
        {"Mie Scattering Coefficient", {"Mie Scattering Coefficient", FieldType::Float}},
        {"Noise Type", {"Noise Type", FieldType::Int32}},
        {"Terrain Height Seed", {"Terrain Height Seed", FieldType::Int32}},
        {"Terrain Max Height (m", {"Terrain Max Height (m", FieldType::Float}},
        {"TEMP", {"TEMP", FieldType::Float}},
        {"DENS", {"DENS", FieldType::Float}},
        {"PHLA", {"PHLA", FieldType::Float}},
        {"Vein Nodes Min", {"Vein Nodes Min", FieldType::Float}},
        {"Vein Nodes Max", {"Vein Nodes Max", FieldType::Float}},
        {"Node Size Min", {"Node Size Min", FieldType::Float}},
        {"Node Size Max", {"Node Size Max", FieldType::Float}},
        {"Unknown", {"Unknown", FieldType::Float}},
        {"Max Angle Offset", {"Max Angle Offset", FieldType::Float}},
        {"Chance to Appear", {"Chance to Appear", FieldType::Float}},
        {"Max Node Offset", {"Max Node Offset", FieldType::Float}},
        {"Chance per Node", {"Chance per Node", FieldType::Float}},
        {"Segment Length Min", {"Segment Length Min", FieldType::Float}},
        {"Segment Length Max", {"Segment Length Max", FieldType::Float}},
        {"Surface Item Chance None", {"Surface Item Chance None", FieldType::Float}},
        {"Blobbiness", {"Blobbiness", FieldType::Float}},
        {"Required Count", {"Required Count", FieldType::Int32}},
        {"Rank", {"Rank", FieldType::Int32}},
        {"CNAM", {"CNAM", FieldType::FormID}},
        {"ANAM", {"ANAM", FieldType::String}},
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}},
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}},
        {"NAM0", {"NAM0", FieldType::String}},
        {"NAM1", {"NAM1", FieldType::String}},
        {"BNAM", {"BNAM", FieldType::String}},
        {"Common", {"Common", FieldType::Float}},
        {"Uncommon", {"Uncommon", FieldType::Float}},
        {"Rare", {"Rare", FieldType::Float}},
        {"Column", {"Column", FieldType::Int32}},
        {"Step", {"Step", FieldType::Float}},
        {"VORV", {"VORV", FieldType::Float}},
        {"VORN", {"VORN", FieldType::Float}},
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Depth Amount", {"Depth Amount", FieldType::Float}},
        {"Red", {"Red", FieldType::Float}},
        {"Green", {"Green", FieldType::Float}},
        {"Blue", {"Blue", FieldType::Float}},
        {"Phytoplankton", {"Phytoplankton", FieldType::Float}},
        {"Sediment", {"Sediment", FieldType::Float}},
        {"Yellow Matter", {"Yellow Matter", FieldType::Float}},
        {"Oceanness", {"Oceanness", FieldType::Float}},
        {"Fog Amount", {"Fog Amount", FieldType::Float}},
        {"Near Fog", {"Near Fog", FieldType::Float}},
        {"Far Fog", {"Far Fog", FieldType::Float}},
        {"Normal Magnitude", {"Normal Magnitude", FieldType::Float}},
        {"Shallow Normal Falloff", {"Shallow Normal Falloff", FieldType::Float}},
        {"Deep Normal Falloff", {"Deep Normal Falloff", FieldType::Float}},
        {"Surface Effect Falloff", {"Surface Effect Falloff", FieldType::Float}},
        {"Force", {"Force", FieldType::Float}},
        {"Velocity", {"Velocity", FieldType::Float}},
        {"Falloff", {"Falloff", FieldType::Float}},
        {"Dampener", {"Dampener", FieldType::Float}},
        {"Starting Size", {"Starting Size", FieldType::Float}},
        {"Layer 1 - Wind Direction", {"Layer 1 - Wind Direction", FieldType::Float}},
        {"Layer 2 - Wind Direction", {"Layer 2 - Wind Direction", FieldType::Float}},
        {"Layer 3 - Wind Direction", {"Layer 3 - Wind Direction", FieldType::Float}},
        {"Layer 1 - Wind Speed", {"Layer 1 - Wind Speed", FieldType::Float}},
        {"Layer 2 - Wind Speed", {"Layer 2 - Wind Speed", FieldType::Float}},
        {"Layer 3 - Wind Speed", {"Layer 3 - Wind Speed", FieldType::Float}},
        {"Layer 1 - Amplitude Scale", {"Layer 1 - Amplitude Scale", FieldType::Float}},
        {"Layer 2 - Amplitude Scale", {"Layer 2 - Amplitude Scale", FieldType::Float}},
        {"Layer 3 - Amplitude Scale", {"Layer 3 - Amplitude Scale", FieldType::Float}},
        {"Layer 1 - UV Scale", {"Layer 1 - UV Scale", FieldType::Float}},
        {"Layer 2 - UV Scale", {"Layer 2 - UV Scale", FieldType::Float}},
        {"Layer 3 - UV Scale", {"Layer 3 - UV Scale", FieldType::Float}},
        {"Layer 1 - Noise Falloff", {"Layer 1 - Noise Falloff", FieldType::Float}},
        {"Layer 2 - Noise Falloff", {"Layer 2 - Noise Falloff", FieldType::Float}},
        {"Layer 3 - Noise Falloff", {"Layer 3 - Noise Falloff", FieldType::Float}},
        {"Flowmap Scale", {"Flowmap Scale", FieldType::Float}},
        {"Roughnes", {"Roughnes", FieldType::Float}},
        {"Sighted Transition (Seconds", {"Sighted Transition (Seconds", FieldType::Float}},
        {"Accuracy Bonus", {"Accuracy Bonus", FieldType::Int32}},
        {"Ammo Capacity", {"Ammo Capacity", FieldType::Int32}},
        {"Projectiles Count", {"Projectiles Count", FieldType::Int32}},
        {"Number of Impact Sounds", {"Number of Impact Sounds", FieldType::Int32}},
        {"Heading Speed", {"Heading Speed", FieldType::Float}},
        {"Pitch Speed", {"Pitch Speed", FieldType::Float}},
        {"Accuracy", {"Accuracy", FieldType::Float}},
        {"Full Power (Seconds", {"Full Power (Seconds", FieldType::Float}},
        {"Min Power Per Shot", {"Min Power Per Shot", FieldType::Float}},
        {"Crit Charge Bonus", {"Crit Charge Bonus", FieldType::Float}},
        {"Base Damage", {"Base Damage", FieldType::Float}},
        {"Range - Min", {"Range - Min", FieldType::Float}},
        {"Range - Max", {"Range - Max", FieldType::Float}},
        {"Out of Range Damage Mult", {"Out of Range Damage Mult", FieldType::Float}},
        {"Crit Damage Mult", {"Crit Damage Mult", FieldType::Float}},
        {"Scale Control Point", {"Scale Control Point", FieldType::Float}},
        {"Crit Chance Inc Mult", {"Crit Chance Inc Mult", FieldType::Float}},
        {"Burst count", {"Burst count", FieldType::Int32}},
        {"Attack (Seconds", {"Attack (Seconds", FieldType::Float}},
        {"Fire (Seconds", {"Fire (Seconds", FieldType::Float}},
        {"Attack Delay (Seconds", {"Attack Delay (Seconds", FieldType::Float}},
        {"Bolt Charge (Seconds", {"Bolt Charge (Seconds", FieldType::Float}},
        {"Shots Per Second", {"Shots Per Second", FieldType::Float}},
        {"Weapon Attack Animation Duration", {"Weapon Attack Animation Duration", FieldType::Float}},
        {"Trigger Threshold - Primary Trigger", {"Trigger Threshold - Primary Trigger", FieldType::Float}},
        {"Trigger Threshold - Second Stage", {"Trigger Threshold - Second Stage", FieldType::Float}},
        {"Burst Delay (Seconds", {"Burst Delay (Seconds", FieldType::Float}},
        {"Base weight", {"Base weight", FieldType::Float}},
        {"Base value", {"Base value", FieldType::Int32}},
        {"Base Speed", {"Base Speed", FieldType::Float}},
        {"Attack Oxygen Cost", {"Attack Oxygen Cost", FieldType::Float}},
        {"Bash Damage", {"Bash Damage", FieldType::Float}},
        {"Reach", {"Reach", FieldType::Float}},
        {"Recharge time", {"Recharge time", FieldType::Float}},
        {"Recharge delay", {"Recharge delay", FieldType::Float}},
        {"Variable Power Transition Duration", {"Variable Power Transition Duration", FieldType::Float}},
        {"Power Damage Multiplier", {"Power Damage Multiplier", FieldType::Float}},
        {"Reload Seconds", {"Reload Seconds", FieldType::Float}},
        {"Reload Speed", {"Reload Speed", FieldType::Float}},
        {"Value - Min", {"Value - Min", FieldType::Float}},
        {"Value - Max", {"Value - Max", FieldType::Float}},
        {"Input - Min", {"Input - Min", FieldType::Float}},
        {"Input - Max", {"Input - Max", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}},
        {"MOD4", {"MOD4", FieldType::String}},
        {"MO4S", {"MO4S", FieldType::Float}},
        {"Color Remapping Index", {"Color Remapping Index", FieldType::Float}},
        {"Attack Action Point Cost", {"Attack Action Point Cost", FieldType::Float}},
        {"Firing Camera Shake Intensity", {"Firing Camera Shake Intensity", FieldType::Float}},
        {"Firing Camera Shake Duration", {"Firing Camera Shake Duration", FieldType::Float}},
        {"AI Firing Arc", {"AI Firing Arc", FieldType::Float}},
        {"Distance From Wall", {"Distance From Wall", FieldType::Float}},
        {"GunUp to GunDown Transition Duration (s", {"GunUp to GunDown Transition Duration (s", FieldType::Float}},
        {"GunDown to GunUp Transition Duration (s", {"GunDown to GunUp Transition Duration (s", FieldType::Float}},
        {"Wind Speed", {"Wind Speed", FieldType::Int32}},
        {"Trans Delta", {"Trans Delta", FieldType::Int32}},
        {"Sun Glare", {"Sun Glare", FieldType::Int32}},
        {"Sun Damage", {"Sun Damage", FieldType::Int32}},
        {"Precipitation - Begin Fade In", {"Precipitation - Begin Fade In", FieldType::Int32}},
        {"Precipitation - End Fade Out", {"Precipitation - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Begin Fade In", {"Thunder/Lightning - Begin Fade In", FieldType::Int32}},
        {"Thunder/Lightning - End Fade Out", {"Thunder/Lightning - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Frequency", {"Thunder/Lightning - Frequency", FieldType::Int32}},
        {"Visual Effect - Begin", {"Visual Effect - Begin", FieldType::Int32}},
        {"Visual Effect - End", {"Visual Effect - End", FieldType::Int32}},
        {"Wind Direction", {"Wind Direction", FieldType::Int32}},
        {"Wind Direction Range", {"Wind Direction Range", FieldType::Int32}},
        {"Wind Turbulance", {"Wind Turbulance", FieldType::Int32}},
        {"NAM7", {"NAM7", FieldType::String}},
        {"ICON", {"ICON", FieldType::String}},
        {"NAMA", {"NAMA", FieldType::Float}},
        {"XWEM", {"XWEM", FieldType::String}},
        {"FOV Mult", {"FOV Mult", FieldType::Float}},
        {"FOV Offset", {"FOV Offset", FieldType::Float}},
        {"Offset Duration", {"Offset Duration", FieldType::Float}}
    }}},
    {"BMMO", {"'Biome Marker'", {

    }}},
    {"BMOD", {"'Bone Modifier'", {
        {"Max Anim Distance", {"Max Anim Distance", FieldType::Float}},
        {"Inner", {"Inner", FieldType::Float}},
        {"Outer", {"Outer", FieldType::Float}}
    }}},
    {"BNDS", {"'Bendable Spline'", {
        {"Default Number of Tiles", {"Default Number of Tiles", FieldType::Float}},
        {"Default Number of Slices", {"Default Number of Slices", FieldType::Int32}},
        {"Wind Settings - Sensibility", {"Wind Settings - Sensibility", FieldType::Float}},
        {"Wind Settings - Flexibility", {"Wind Settings - Flexibility", FieldType::Float}}
    }}},
    {"BODV", {"Configuration", {
        {"Unknown", {"Unknown", FieldType::Int32}}
    }}},
    {"BOOK", {"'Book'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}}
    }}},
    {"BPD2", {"Data", {
        {"Damage Mult", {"Damage Mult", FieldType::Float}}
    }}},
    {"BPTD", {"'Body Part Data'", {
        {"BPNN", {"BPNN", FieldType::String}},
        {"BPNT", {"BPNT", FieldType::String}},
        {"Damage Mult", {"Damage Mult", FieldType::Float}},
        {"Health Percent", {"Health Percent", FieldType::Int32}},
        {"To Hit Chance", {"To Hit Chance", FieldType::Int32}},
        {"On Cripple - Debris Scale", {"On Cripple - Debris Scale", FieldType::Float}},
        {"On Cripple - Debris Count", {"On Cripple - Debris Count", FieldType::Int32}},
        {"On Cripple - Decal Count", {"On Cripple - Decal Count", FieldType::Int32}},
        {"NAM4", {"NAM4", FieldType::String}},
        {"ENAM", {"ENAM", FieldType::String}},
        {"FNAM", {"FNAM", FieldType::String}},
        {"DNAM", {"DNAM", FieldType::String}}
    }}},
    {"BSMS", {"Range", {
        {"Min Y", {"Min Y", FieldType::Float}},
        {"Min Z", {"Min Z", FieldType::Float}},
        {"Max Y", {"Max Y", FieldType::Float}},
        {"Max Z", {"Max Z", FieldType::Float}}
    }}},
    {"CAMS", {"'Camera Shot'", {
        {"Player", {"Player", FieldType::Float}},
        {"Target", {"Target", FieldType::Float}},
        {"Global", {"Global", FieldType::Float}},
        {"Max Time", {"Max Time", FieldType::Float}},
        {"Min Time", {"Min Time", FieldType::Float}},
        {"Target % Between Actors", {"Target % Between Actors", FieldType::Float}},
        {"Near Target Distance", {"Near Target Distance", FieldType::Float}},
        {"Location Spring", {"Location Spring", FieldType::Float}},
        {"Target Spring", {"Target Spring", FieldType::Float}},
        {"GNAM", {"GNAM", FieldType::String}}
    }}},
    {"CELL", {"'Cell'", {
        {"Fog Near", {"Fog Near", FieldType::Float}},
        {"Fog Far", {"Fog Far", FieldType::Float}},
        {"Directional Rotation XY", {"Directional Rotation XY", FieldType::Int32}},
        {"Directional Rotation Z", {"Directional Rotation Z", FieldType::Int32}},
        {"Gravity Scale", {"Gravity Scale", FieldType::Float}},
        {"Fog Clip Distance", {"Fog Clip Distance", FieldType::Float}},
        {"Fog Power", {"Fog Power", FieldType::Float}},
        {"Fog Max", {"Fog Max", FieldType::Float}},
        {"Light Fade Begin", {"Light Fade Begin", FieldType::Float}},
        {"Light Fade End", {"Light Fade End", FieldType::Float}},
        {"Near Height Mid", {"Near Height Mid", FieldType::Float}},
        {"Near Height Range", {"Near Height Range", FieldType::Float}},
        {"High Density Scale", {"High Density Scale", FieldType::Float}},
        {"Fog Near Scale", {"Fog Near Scale", FieldType::Float}},
        {"Fog Far Scale", {"Fog Far Scale", FieldType::Float}},
        {"Fog High Near Scale", {"Fog High Near Scale", FieldType::Float}},
        {"Fog High Far Scale", {"Fog High Far Scale", FieldType::Float}},
        {"Far Height Mid", {"Far Height Mid", FieldType::Float}},
        {"Far Height Range", {"Far Height Range", FieldType::Float}},
        {"XCLW", {"XCLW", FieldType::Float}}
    }}},
    {"CHAL", {"'Challenge'", {

    }}},
    {"CLAS", {"'Class'", {

    }}},
    {"CLDF", {"'Clouds'", {

    }}},
    {"CLFM", {"'Color'", {
        {"Remapping Index", {"Remapping Index", FieldType::Float}}
    }}},
    {"CLMT", {"'Climate'", {
        {"Chance", {"Chance", FieldType::Int32}}
    }}},
    {"CNDF", {"'Condition Form'", {

    }}},
    {"CNTO", {"[0]", {
        {"Count", {"Count", FieldType::Int32}}
    }}},
    {"COBJ", {"'Constructible Object'", {
        {"Rank", {"Rank", FieldType::Int32}},
        {"SNAM", {"SNAM", FieldType::Float}}
    }}},
    {"COLL", {"'Collision Layer'", {

    }}},
    {"CONT", {"'Container'", {

    }}},
    {"CPTH", {"'Camera Path'", {

    }}},
    {"CRVA", {"Crime Values", {
        {"Murder", {"Murder", FieldType::Int32}},
        {"Assault", {"Assault", FieldType::Int32}},
        {"Trespass", {"Trespass", FieldType::Int32}},
        {"Pickpocket", {"Pickpocket", FieldType::Int32}},
        {"Unknown", {"Unknown", FieldType::Int32}},
        {"Steal Multiplier", {"Steal Multiplier", FieldType::Float}},
        {"Escape", {"Escape", FieldType::Int32}},
        {"Piracy", {"Piracy", FieldType::Int32}},
        {"Smuggle Multiplier", {"Smuggle Multiplier", FieldType::Float}}
    }}},
    {"CSGD", {"General", {
        {"Charging - Throw Max Targets", {"Charging - Throw Max Targets", FieldType::Int32}}
    }}},
    {"CSSD", {"Space Detection", {
        {"Detection Rating 1", {"Detection Rating 1", FieldType::Float}},
        {"Detection Rating 2", {"Detection Rating 2", FieldType::Float}},
        {"Detection Rating 3", {"Detection Rating 3", FieldType::Float}}
    }}},
    {"CSTY", {"'Combat Style'", {
        {"Charging - Throw Max Targets", {"Charging - Throw Max Targets", FieldType::Int32}},
        {"Disengage Maneuver Chance", {"Disengage Maneuver Chance", FieldType::Float}},
        {"Detection Rating 1", {"Detection Rating 1", FieldType::Float}},
        {"Detection Rating 2", {"Detection Rating 2", FieldType::Float}},
        {"Detection Rating 3", {"Detection Rating 3", FieldType::Float}}
    }}},
    {"CUR3", {"'Curve 3D'", {

    }}},
    {"CURV", {"'Curve Table'", {

    }}},
    {"DAT2", {"Data", {
        {"Male Height", {"Male Height", FieldType::Float}},
        {"Female Height", {"Female Height", FieldType::Float}},
        {"Thin", {"Thin", FieldType::Float}},
        {"Muscular", {"Muscular", FieldType::Float}},
        {"Fat", {"Fat", FieldType::Float}}
    }}},
    {"DATA", {"Lighting", {
        {"Fog Near", {"Fog Near", FieldType::Float}},
        {"Fog Far", {"Fog Far", FieldType::Float}},
        {"Directional Rotation XY", {"Directional Rotation XY", FieldType::Int32}},
        {"Directional Rotation Z", {"Directional Rotation Z", FieldType::Int32}},
        {"Directional Fade", {"Directional Fade", FieldType::Float}},
        {"Fog Clip Distance", {"Fog Clip Distance", FieldType::Float}},
        {"Fog Power", {"Fog Power", FieldType::Float}},
        {"Light Fade Distance Start", {"Light Fade Distance Start", FieldType::Float}},
        {"Light Fade Distance Stop", {"Light Fade Distance Stop", FieldType::Float}},
        {"Height Mid", {"Height Mid", FieldType::Float}},
        {"Height Range", {"Height Range", FieldType::Float}},
        {"High Density Scale", {"High Density Scale", FieldType::Float}},
        {"Fog Near Scale", {"Fog Near Scale", FieldType::Float}},
        {"Fog Far Scale", {"Fog Far Scale", FieldType::Float}},
        {"High Near Scale", {"High Near Scale", FieldType::Float}},
        {"High Far Scale", {"High Far Scale", FieldType::Float}},
        {"Far Height Mid", {"Far Height Mid", FieldType::Float}},
        {"Far Height Range", {"Far Height Range", FieldType::Float}}
    }}},
    {"DEBR", {"'Debris'", {

    }}},
    {"DEST", {"Header", {
        {"Health", {"Health", FieldType::Int32}},
        {"Stage Count", {"Stage Count", FieldType::Int32}}
    }}},
    {"DEVT", {"Sound Detection", {
        {"Radius", {"Radius", FieldType::Float}}
    }}},
    {"DFOB", {"'Default Object'", {
        {"DATA", {"DATA", FieldType::FormID}}
    }}},
    {"DIAL", {"'Dialog Topic'", {
        {"PNAM", {"PNAM", FieldType::Float}}
    }}},
    {"DLBR", {"'Dialog Branch'", {

    }}},
    {"DLVW", {"'Dialog View'", {

    }}},
    {"DMGT", {"'Damage Type'", {

    }}},
    {"DNAM", {"Data", {
        {"Fall Off", {"Fall Off", FieldType::Float}},
        {"Alpha Fade In Time", {"Alpha Fade In Time", FieldType::Float}},
        {"Full Alpha Time", {"Full Alpha Time", FieldType::Float}},
        {"Alpha Fade Out Time", {"Alpha Fade Out Time", FieldType::Float}},
        {"Persistent Alpha Ratio [0-1]", {"Persistent Alpha Ratio [0-1]", FieldType::Float}},
        {"Alpha Pulse Amplitude", {"Alpha Pulse Amplitude", FieldType::Float}},
        {"Alpha Pulse Frequency", {"Alpha Pulse Frequency", FieldType::Float}},
        {"Full Alpha Ratio [0-1]", {"Full Alpha Ratio [0-1]", FieldType::Float}}
    }}},
    {"DOBJ", {"'Default Object Manager'", {
        {"Object ID", {"Object ID", FieldType::FormID}}
    }}},
    {"DODT", {"Decal Data", {
        {"Min Width", {"Min Width", FieldType::Float}},
        {"Max Width", {"Max Width", FieldType::Float}},
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Depth", {"Depth", FieldType::Float}},
        {"Alpha", {"Alpha", FieldType::Float}}
    }}},
    {"DOOR", {"'Door'", {

    }}},
    {"DSTD", {"Data", {
        {"Health %", {"Health %", FieldType::Int32}},
        {"Index", {"Index", FieldType::Int32}},
        {"Model Damage Stage", {"Model Damage Stage", FieldType::Int32}}
    }}},
    {"DUAL", {"'Dual Cast Data'", {

    }}},
    {"EFSH", {"'Effect Shader'", {
        {"Fall Off", {"Fall Off", FieldType::Float}},
        {"Alpha Fade In Time", {"Alpha Fade In Time", FieldType::Float}},
        {"Full Alpha Time", {"Full Alpha Time", FieldType::Float}},
        {"Alpha Fade Out Time", {"Alpha Fade Out Time", FieldType::Float}},
        {"Persistent Alpha Ratio [0-1]", {"Persistent Alpha Ratio [0-1]", FieldType::Float}},
        {"Alpha Pulse Amplitude", {"Alpha Pulse Amplitude", FieldType::Float}},
        {"Alpha Pulse Frequency", {"Alpha Pulse Frequency", FieldType::Float}},
        {"Full Alpha Ratio [0-1]", {"Full Alpha Ratio [0-1]", FieldType::Float}},
        {"Start Time", {"Start Time", FieldType::Float}},
        {"Stop Time", {"Stop Time", FieldType::Float}},
        {"Start Val", {"Start Val", FieldType::Float}},
        {"Stop Val", {"Stop Val", FieldType::Float}},
        {"Bone Depth", {"Bone Depth", FieldType::Int32}}
    }}},
    {"EFSQ", {"'Effect Sequence'", {

    }}},
    {"ENAM", {"Height", {
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}}
    }}},
    {"ENCH", {"'Enchantment'", {
        {"Enchantment Cost", {"Enchantment Cost", FieldType::Int32}},
        {"Enchantment Amount", {"Enchantment Amount", FieldType::Int32}},
        {"Charge Time", {"Charge Time", FieldType::Float}}
    }}},
    {"ENIT", {"Effect Data", {
        {"Value", {"Value", FieldType::Int32}}
    }}},
    {"EORI", {"Override - Surface Block Rotations", {
        {"Column", {"Column", FieldType::Int32}}
    }}},
    {"EQUP", {"'Equip Type'", {

    }}},
    {"EXPL", {"'Explosion'", {
        {"Force", {"Force", FieldType::Float}},
        {"Damage", {"Damage", FieldType::Float}},
        {"Inner Radius", {"Inner Radius", FieldType::Float}},
        {"Outer Radius", {"Outer Radius", FieldType::Float}},
        {"IS Radius", {"IS Radius", FieldType::Float}},
        {"Vertical Offset Mult", {"Vertical Offset Mult", FieldType::Float}},
        {"Placed Object AutoFade Delay", {"Placed Object AutoFade Delay", FieldType::Float}},
        {"Count", {"Count", FieldType::Int32}},
        {"Duration", {"Duration", FieldType::Float}}
    }}},
    {"EYES", {"'Eyes'", {

    }}},
    {"FACT", {"'Faction'", {
        {"Murder", {"Murder", FieldType::Int32}},
        {"Assault", {"Assault", FieldType::Int32}},
        {"Trespass", {"Trespass", FieldType::Int32}},
        {"Pickpocket", {"Pickpocket", FieldType::Int32}},
        {"Unknown", {"Unknown", FieldType::Int32}},
        {"Steal Multiplier", {"Steal Multiplier", FieldType::Float}},
        {"Escape", {"Escape", FieldType::Int32}},
        {"Piracy", {"Piracy", FieldType::Int32}},
        {"Smuggle Multiplier", {"Smuggle Multiplier", FieldType::Float}},
        {"Start Hour", {"Start Hour", FieldType::Int32}},
        {"End Hour", {"End Hour", FieldType::Int32}},
        {"Radius", {"Radius", FieldType::Float}},
        {"Search Radius", {"Search Radius", FieldType::Float}},
        {"Min Herd Members", {"Min Herd Members", FieldType::Int32}},
        {"Max Herd Members", {"Max Herd Members", FieldType::Int32}},
        {"Idle Chatter Min Time", {"Idle Chatter Min Time", FieldType::Float}},
        {"Idle Chatter Max Time", {"Idle Chatter Max Time", FieldType::Float}},
        {"GRPH", {"GRPH", FieldType::Float}}
    }}},
    {"FFKW", {"'Form Folder Keyword List'", {

    }}},
    {"FLBD", {"Barndoors", {
        {"Left", {"Left", FieldType::Float}},
        {"Bottom", {"Bottom", FieldType::Float}},
        {"Right", {"Right", FieldType::Float}},
        {"Top", {"Top", FieldType::Float}},
        {"Falloff Intensity", {"Falloff Intensity", FieldType::Float}}
    }}},
    {"FLCS", {"Contact Shadows", {
        {"Thickness", {"Thickness", FieldType::Float}},
        {"Fade Length", {"Fade Length", FieldType::Float}},
        {"Fade Start", {"Fade Start", FieldType::Float}},
        {"Max Distance", {"Max Distance", FieldType::Float}},
        {"Proximity Limit", {"Proximity Limit", FieldType::Float}}
    }}},
    {"FLEE", {"Flee Settings", {
        {"Flee Distance GLOB", {"Flee Distance GLOB", FieldType::FormID}},
        {"Safe Timer GLOB", {"Safe Timer GLOB", FieldType::FormID}},
        {"Chance of Diversion Animation GLOB", {"Chance of Diversion Animation GLOB", FieldType::FormID}},
        {"Flee Distance", {"Flee Distance", FieldType::Float}},
        {"Safe Timer", {"Safe Timer", FieldType::Float}},
        {"Chance of Diversion Animation", {"Chance of Diversion Animation", FieldType::Float}}
    }}},
    {"FLOR", {"'Flora'", {
        {"Spring", {"Spring", FieldType::Int32}},
        {"Summer ", {"Summer ", FieldType::Int32}},
        {"Fall", {"Fall", FieldType::Int32}},
        {"Winter", {"Winter", FieldType::Int32}},
        {"BNAM", {"BNAM", FieldType::Float}},
        {"FMAH", {"FMAH", FieldType::Float}},
        {"FMIH", {"FMIH", FieldType::Float}}
    }}},
    {"FLST", {"'FormID List'", {
        {"LNAM", {"LNAM", FieldType::FormID}}
    }}},
    {"FNAM", {"Data", {
        {"X offset", {"X offset", FieldType::Float}},
        {"Y offset", {"Y offset", FieldType::Float}},
        {"Texture Width", {"Texture Width", FieldType::Int32}},
        {"Texture Height", {"Texture Height", FieldType::Int32}},
        {"Content Width", {"Content Width", FieldType::Int32}},
        {"Content Height", {"Content Height", FieldType::Int32}}
    }}},
    {"FOGV", {"'Fog Volume'", {

    }}},
    {"FORC", {"'Force Data'", {

    }}},
    {"FSTP", {"'Footstep'", {

    }}},
    {"FSTS", {"'Footstep Set'", {
        {"Walking Count", {"Walking Count", FieldType::Int32}},
        {"Running Count", {"Running Count", FieldType::Int32}},
        {"Sprinting Count", {"Sprinting Count", FieldType::Int32}},
        {"Sneaking Count", {"Sneaking Count", FieldType::Int32}},
        {"Swimming Count", {"Swimming Count", FieldType::Int32}}
    }}},
    {"FURN", {"'Furniture'", {
        {"XMRK", {"XMRK", FieldType::String}},
        {"Name", {"Name", FieldType::String}},
        {"Model FileName", {"Model FileName", FieldType::String}}
    }}},
    {"FXPD", {"'Facial Expression'", {
        {"MNAM", {"MNAM", FieldType::String}},
        {"MWGT", {"MWGT", FieldType::Float}}
    }}},
    {"GBFM", {"'Generic Base Form'", {
        {"STRV", {"STRV", FieldType::String}}
    }}},
    {"GBFT", {"'Generic Base Form Template'", {
        {"STRV", {"STRV", FieldType::String}}
    }}},
    {"GCVR", {"'Ground Cover'", {

    }}},
    {"GLOB", {"'Global'", {

    }}},
    {"GMST", {"'Game Setting'", {
        {"Int", {"Int", FieldType::Int32}},
        {"Float", {"Float", FieldType::Float}},
        {"UInt", {"UInt", FieldType::Int32}}
    }}},
    {"GNAM", {"Galaxy Data", {
        {"Parent Planet ID", {"Parent Planet ID", FieldType::Int32}},
        {"Planet ID", {"Planet ID", FieldType::Int32}}
    }}},
    {"GPOD", {"Data Range", {
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}},
        {"Step", {"Step", FieldType::Float}},
        {"VORV", {"VORV", FieldType::Float}},
        {"VORN", {"VORN", FieldType::Float}}
    }}},
    {"GPOF", {"'Gameplay Option'", {
        {"VNAM", {"VNAM", FieldType::Float}},
        {"WNAM", {"WNAM", FieldType::Float}},
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}},
        {"Step", {"Step", FieldType::Float}},
        {"VORV", {"VORV", FieldType::Float}},
        {"VORN", {"VORN", FieldType::Float}}
    }}},
    {"GPOG", {"'Gameplay Options Group'", {

    }}},
    {"GRAS", {"'Grass'", {
        {"Wind Frequency", {"Wind Frequency", FieldType::Float}},
        {"Above Water Clamp - Value", {"Above Water Clamp - Value", FieldType::Float}},
        {"Below Water Clamp - Value", {"Below Water Clamp - Value", FieldType::Float}},
        {"Max Density", {"Max Density", FieldType::Int32}},
        {"Min Slope", {"Min Slope", FieldType::Int32}},
        {"Max Slope", {"Max Slope", FieldType::Int32}}
    }}},
    {"HAZD", {"'Hazard'", {
        {"Radius", {"Radius", FieldType::Float}},
        {"Lifetime", {"Lifetime", FieldType::Float}},
        {"Image Space Radius", {"Image Space Radius", FieldType::Float}},
        {"Target Interval", {"Target Interval", FieldType::Float}},
        {"Full Effect Radius", {"Full Effect Radius", FieldType::Float}},
        {"Taper Weight", {"Taper Weight", FieldType::Float}},
        {"Taper Curse", {"Taper Curse", FieldType::Float}},
        {"Gravity", {"Gravity", FieldType::Float}},
        {"Limit", {"Limit", FieldType::Int32}}
    }}},
    {"HDPT", {"'Head Part'", {
        {"NAM2", {"NAM2", FieldType::String}},
        {"NAM3", {"NAM3", FieldType::String}}
    }}},
    {"HERD", {"Unknown", {
        {"Search Radius", {"Search Radius", FieldType::Float}},
        {"Min Herd Members", {"Min Herd Members", FieldType::Int32}},
        {"Max Herd Members", {"Max Herd Members", FieldType::Int32}},
        {"Idle Chatter Min Time", {"Idle Chatter Min Time", FieldType::Float}},
        {"Idle Chatter Max Time", {"Idle Chatter Max Time", FieldType::Float}}
    }}},
    {"HNAM", {"Unknown", {
        {"Density", {"Density", FieldType::Float}},
        {"Heat", {"Heat", FieldType::Float}},
        {"Hydro", {"Hydro", FieldType::Float}},
        {"Inner HZ", {"Inner HZ", FieldType::Float}},
        {"Outer HZ", {"Outer HZ", FieldType::Float}},
        {"Peri. Angle", {"Peri. Angle", FieldType::Float}},
        {"Start angle in deg", {"Start angle in deg", FieldType::Float}},
        {"Year length in days", {"Year length in days", FieldType::Float}},
        {"Asteroids", {"Asteroids", FieldType::Int32}},
        {"Random Seed", {"Random Seed", FieldType::Int32}}
    }}},
    {"IDLE", {"'Animation'", {
        {"DNAM", {"DNAM", FieldType::String}},
        {"ENAM", {"ENAM", FieldType::String}},
        {"GNAM", {"GNAM", FieldType::String}}
    }}},
    {"IDLM", {"'Idle Marker'", {

    }}},
    {"IMAD", {"'Image Space Adapter'", {

    }}},
    {"IMGS", {"'Image Space'", {

    }}},
    {"INFO", {"'Dialog response'", {
        {"Emotion Out", {"Emotion Out", FieldType::Float}},
        {"NAM2", {"NAM2", FieldType::String}},
        {"NAM3", {"NAM3", FieldType::String}},
        {"NAM4", {"NAM4", FieldType::String}},
        {"On Begin", {"On Begin", FieldType::Int32}},
        {"On End", {"On End", FieldType::Int32}},
        {"NAM0", {"NAM0", FieldType::String}}
    }}},
    {"INGR", {"'Ingredient'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"Ingredient Value", {"Ingredient Value", FieldType::Int32}}
    }}},
    {"INNR", {"'Instance Naming Rules'", {
        {"Value", {"Value", FieldType::Float}}
    }}},
    {"IPCT", {"'Impact'", {
        {"Effect - Duration", {"Effect - Duration", FieldType::Float}},
        {"Angle Threshold", {"Angle Threshold", FieldType::Float}},
        {"Placement Radius", {"Placement Radius", FieldType::Float}},
        {"FNAM", {"FNAM", FieldType::Float}},
        {"INAM", {"INAM", FieldType::Float}}
    }}},
    {"IPDS", {"'Impact Data Set'", {

    }}},
    {"IRES", {"'Resource'", {
        {"GNAM", {"GNAM", FieldType::String}}
    }}},
    {"KEYM", {"'Key'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}}
    }}},
    {"KNAM", {"Biome Noise", {
        {"Noise Type", {"Noise Type", FieldType::Int32}},
        {"Terrain Height Seed", {"Terrain Height Seed", FieldType::Int32}},
        {"Terrain Max Height (m", {"Terrain Max Height (m", FieldType::Float}}
    }}},
    {"KSSM", {"'Sound Keyword Mapping'", {

    }}},
    {"KYWD", {"'Keyword'", {
        {"DNAM", {"DNAM", FieldType::String}},
        {"ENAM", {"ENAM", FieldType::String}}
    }}},
    {"LAYR", {"'Layer'", {

    }}},
    {"LCRT", {"'Location Reference Type'", {
        {"DNAM", {"DNAM", FieldType::String}},
        {"ENAM", {"ENAM", FieldType::String}}
    }}},
    {"LCTN", {"'Location'", {
        {"Faction Rank", {"Faction Rank", FieldType::Int32}},
        {"Min Level", {"Min Level", FieldType::Int32}},
        {"Max Level", {"Max Level", FieldType::Int32}},
        {"RNAM", {"RNAM", FieldType::Float}},
        {"ANAM", {"ANAM", FieldType::Float}},
        {"TNAM", {"TNAM", FieldType::Float}},
        {"IBIN", {"IBIN", FieldType::String}},
        {"SNAM", {"SNAM", FieldType::String}},
        {"Object ID", {"Object ID", FieldType::FormID}},
        {"Fog Near", {"Fog Near", FieldType::Float}},
        {"Fog Far", {"Fog Far", FieldType::Float}},
        {"Directional Rotation XY", {"Directional Rotation XY", FieldType::Int32}},
        {"Directional Rotation Z", {"Directional Rotation Z", FieldType::Int32}},
        {"Directional Fade", {"Directional Fade", FieldType::Float}},
        {"Fog Clip Distance", {"Fog Clip Distance", FieldType::Float}},
        {"Fog Power", {"Fog Power", FieldType::Float}},
        {"Light Fade Distance Start", {"Light Fade Distance Start", FieldType::Float}},
        {"Light Fade Distance Stop", {"Light Fade Distance Stop", FieldType::Float}},
        {"Height Mid", {"Height Mid", FieldType::Float}},
        {"Height Range", {"Height Range", FieldType::Float}},
        {"High Density Scale", {"High Density Scale", FieldType::Float}},
        {"Fog Near Scale", {"Fog Near Scale", FieldType::Float}},
        {"Fog Far Scale", {"Fog Far Scale", FieldType::Float}},
        {"High Near Scale", {"High Near Scale", FieldType::Float}},
        {"High Far Scale", {"High Far Scale", FieldType::Float}},
        {"Far Height Mid", {"Far Height Mid", FieldType::Float}},
        {"Far Height Range", {"Far Height Range", FieldType::Float}},
        {"Priority", {"Priority", FieldType::Int32}},
        {"Ducking (dB", {"Ducking (dB", FieldType::Int32}},
        {"Walking Count", {"Walking Count", FieldType::Int32}},
        {"Running Count", {"Running Count", FieldType::Int32}},
        {"Sprinting Count", {"Sprinting Count", FieldType::Int32}},
        {"Sneaking Count", {"Sneaking Count", FieldType::Int32}},
        {"Swimming Count", {"Swimming Count", FieldType::Int32}},
        {"HNAM", {"HNAM", FieldType::Float}},
        {"FLTV", {"FLTV", FieldType::Float}},
        {"DNAM", {"DNAM", FieldType::Float}},
        {"Point", {"Point", FieldType::Float}},
        {"NAM0", {"NAM0", FieldType::String}},
        {"On Start", {"On Start", FieldType::Int32}},
        {"On Completion", {"On Completion", FieldType::Int32}},
        {"SNOT", {"SNOT", FieldType::String}},
        {"DMAX", {"DMAX", FieldType::Float}},
        {"DMIN", {"DMIN", FieldType::Float}},
        {"PAPN", {"PAPN", FieldType::String}},
        {"SSPN", {"SSPN", FieldType::String}},
        {"VCLR", {"VCLR", FieldType::Float}},
        {"VNML", {"VNML", FieldType::Float}},
        {"LVCR", {"LVCR", FieldType::Float}},
        {"BTXT", {"BTXT", FieldType::Float}},
        {"On Begin", {"On Begin", FieldType::Int32}},
        {"On End", {"On End", FieldType::Int32}},
        {"NNAM", {"NNAM", FieldType::String}},
        {"MPRT", {"MPRT", FieldType::String}},
        {"FPRT", {"FPRT", FieldType::String}},
        {"MCHT", {"MCHT", FieldType::String}},
        {"FCHT", {"FCHT", FieldType::String}},
        {"Unused", {"Unused", FieldType::Float}},
        {"Walk", {"Walk", FieldType::Float}},
        {"Jog", {"Jog", FieldType::Float}},
        {"Run", {"Run", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}},
        {"Sprint", {"Sprint", FieldType::Float}},
        {"MNAM", {"MNAM", FieldType::String}},
        {"LNAM", {"LNAM", FieldType::Float}},
        {"KNAM", {"KNAM", FieldType::Float}},
        {"Remapping Index", {"Remapping Index", FieldType::Float}},
        {"Wind Frequency", {"Wind Frequency", FieldType::Float}},
        {"Above Water Clamp - Value", {"Above Water Clamp - Value", FieldType::Float}},
        {"Below Water Clamp - Value", {"Below Water Clamp - Value", FieldType::Float}},
        {"Max Density", {"Max Density", FieldType::Int32}},
        {"Min Slope", {"Min Slope", FieldType::Int32}},
        {"Max Slope", {"Max Slope", FieldType::Int32}},
        {"ENAM", {"ENAM", FieldType::String}},
        {"GNAM", {"GNAM", FieldType::String}},
        {"Emotion Out", {"Emotion Out", FieldType::Float}},
        {"NAM2", {"NAM2", FieldType::String}},
        {"NAM3", {"NAM3", FieldType::String}},
        {"NAM4", {"NAM4", FieldType::String}},
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"Ingredient Value", {"Ingredient Value", FieldType::Int32}},
        {"Time", {"Time", FieldType::Int32}},
        {"Radius", {"Radius", FieldType::Float}},
        {"Falloff Exponent", {"Falloff Exponent", FieldType::Float}},
        {"FOV", {"FOV", FieldType::Float}},
        {"Near Clip", {"Near Clip", FieldType::Float}},
        {"Period", {"Period", FieldType::Float}},
        {"Intensity Amplitude", {"Intensity Amplitude", FieldType::Float}},
        {"Movement Amplitude", {"Movement Amplitude", FieldType::Float}},
        {"Shadow Offset", {"Shadow Offset", FieldType::Float}},
        {"Inner FOV", {"Inner FOV", FieldType::Float}},
        {"PBR - Light Temperature (K", {"PBR - Light Temperature (K", FieldType::Int32}},
        {"PBR - Luminous Power (lm", {"PBR - Luminous Power (lm", FieldType::Int32}},
        {"Adaptive Light Ec", {"Adaptive Light Ec", FieldType::Float}},
        {"Adaptive Light Ev 100 Min", {"Adaptive Light Ev 100 Min", FieldType::Float}},
        {"Adaptive Light Ev 100 Max", {"Adaptive Light Ev 100 Max", FieldType::Float}},
        {"Radius Falloff Exponent", {"Radius Falloff Exponent", FieldType::Float}},
        {"Left", {"Left", FieldType::Float}},
        {"Bottom", {"Bottom", FieldType::Float}},
        {"Right", {"Right", FieldType::Float}},
        {"Top", {"Top", FieldType::Float}},
        {"Falloff Intensity", {"Falloff Intensity", FieldType::Float}},
        {"FVLD", {"FVLD", FieldType::Float}},
        {"ICON", {"ICON", FieldType::String}},
        {"Min", {"Min", FieldType::Int32}},
        {"Max", {"Max", FieldType::Int32}},
        {"BNAM", {"BNAM", FieldType::String}},
        {"Friction", {"Friction", FieldType::Int32}},
        {"Restitution", {"Restitution", FieldType::Int32}},
        {"Chance", {"Chance", FieldType::Int32}},
        {"Delay Time", {"Delay Time", FieldType::Float}},
        {"Score", {"Score", FieldType::Float}},
        {"Spellmaking - Area", {"Spellmaking - Area", FieldType::Float}},
        {"Spellmaking - Casting Time", {"Spellmaking - Casting Time", FieldType::Float}},
        {"Base Cost", {"Base Cost", FieldType::Float}},
        {"Dual Casting - Scale", {"Dual Casting - Scale", FieldType::Float}},
        {"Minimum Skill Level", {"Minimum Skill Level", FieldType::Int32}},
        {"Second AV Weight", {"Second AV Weight", FieldType::Float}},
        {"Skill Usage Multiplier", {"Skill Usage Multiplier", FieldType::Float}},
        {"Taper Curve", {"Taper Curve", FieldType::Float}},
        {"Taper Duration", {"Taper Duration", FieldType::Float}},
        {"Taper Weight", {"Taper Weight", FieldType::Float}},
        {"Count", {"Count", FieldType::Int32}},
        {"Rank", {"Rank", FieldType::Int32}},
        {"XP Value Offset", {"XP Value Offset", FieldType::Int32}},
        {"Level", {"Level", FieldType::Int32}},
        {"Calc min level", {"Calc min level", FieldType::Int32}},
        {"Calc max level", {"Calc max level", FieldType::Int32}},
        {"Disposition Base", {"Disposition Base", FieldType::Int32}},
        {"Max Number Of Times To React", {"Max Number Of Times To React", FieldType::Float}},
        {"Reaction Radius", {"Reaction Radius", FieldType::Float}},
        {"Exit Radius", {"Exit Radius", FieldType::Float}},
        {"Max Herd Members To Animate", {"Max Herd Members To Animate", FieldType::Float}},
        {"Number of Warnings Before Attack", {"Number of Warnings Before Attack", FieldType::Float}},
        {"Warn Timer On Warn/Attack", {"Warn Timer On Warn/Attack", FieldType::Float}},
        {"Cool Down Timer", {"Cool Down Timer", FieldType::Float}},
        {"Flee Distance GLOB", {"Flee Distance GLOB", FieldType::FormID}},
        {"Safe Timer GLOB", {"Safe Timer GLOB", FieldType::FormID}},
        {"Chance of Diversion Animation GLOB", {"Chance of Diversion Animation GLOB", FieldType::FormID}},
        {"Flee Distance", {"Flee Distance", FieldType::Float}},
        {"Safe Timer", {"Safe Timer", FieldType::Float}},
        {"Chance of Diversion Animation", {"Chance of Diversion Animation", FieldType::Float}},
        {"Calculated Health", {"Calculated Health", FieldType::Int32}},
        {"Calculated Action Points", {"Calculated Action Points", FieldType::Int32}},
        {"Far Away Model Distance", {"Far Away Model Distance", FieldType::Int32}},
        {"Geared Up Weapons", {"Geared Up Weapons", FieldType::Int32}},
        {"Thin", {"Thin", FieldType::Float}},
        {"Muscular", {"Muscular", FieldType::Float}},
        {"Fat", {"Fat", FieldType::Float}},
        {"QNAM", {"QNAM", FieldType::String}},
        {"VNAM", {"VNAM", FieldType::String}},
        {"Head", {"Head", FieldType::Float}},
        {"Upper Torso", {"Upper Torso", FieldType::Float}},
        {"Arms", {"Arms", FieldType::Float}},
        {"Lower Torso", {"Lower Torso", FieldType::Float}},
        {"Legs", {"Legs", FieldType::Float}},
        {"FMRS", {"FMRS", FieldType::Float}},
        {"FMRG", {"FMRG", FieldType::String}},
        {"BMPN", {"BMPN", FieldType::String}},
        {"BMPV", {"BMPV", FieldType::Float}},
        {"HCOL", {"HCOL", FieldType::String}},
        {"FHCL", {"FHCL", FieldType::String}},
        {"BCOL", {"BCOL", FieldType::String}},
        {"ECOL", {"ECOL", FieldType::String}},
        {"JCOL", {"JCOL", FieldType::String}},
        {"TETC", {"TETC", FieldType::String}},
        {"Acceleration (m", {"Acceleration (m", FieldType::Float}},
        {"Deceleration (m", {"Deceleration (m", FieldType::Float}},
        {"Angular Acceleration (deg", {"Angular Acceleration (deg", FieldType::Float}},
        {"Angular Tolerance (deg", {"Angular Tolerance (deg", FieldType::Float}},
        {"Flight Radius", {"Flight Radius", FieldType::Float}},
        {"Injured Health Pct", {"Injured Health Pct", FieldType::Float}},
        {"Health %", {"Health %", FieldType::Float}},
        {"Recover Chance", {"Recover Chance", FieldType::Float}},
        {"Time Min", {"Time Min", FieldType::Float}},
        {"Time Max", {"Time Max", FieldType::Float}},
        {"Health Drain Rate", {"Health Drain Rate", FieldType::Float}},
        {"Debris Scale", {"Debris Scale", FieldType::Float}},
        {"Debris Count", {"Debris Count", FieldType::Int32}},
        {"Decal Count", {"Decal Count", FieldType::Int32}},
        {"Recover Chance On Damage Received", {"Recover Chance On Damage Received", FieldType::Float}},
        {"Health After Recovery", {"Health After Recovery", FieldType::Float}},
        {"Immunity Duration After Recovery", {"Immunity Duration After Recovery", FieldType::Float}},
        {"Index", {"Index", FieldType::Int32}},
        {"TTET", {"TTET", FieldType::String}},
        {"Alpha", {"Alpha", FieldType::Float}},
        {"Template Index", {"Template Index", FieldType::Int32}},
        {"TTED", {"TTED", FieldType::Float}},
        {"MPGN", {"MPGN", FieldType::String}},
        {"MPGM", {"MPGM", FieldType::String}},
        {"MPPM", {"MPPM", FieldType::String}},
        {"FMRU", {"FMRU", FieldType::String}},
        {"Month", {"Month", FieldType::Int32}},
        {"Date", {"Date", FieldType::Int32}},
        {"Minute", {"Minute", FieldType::Int32}},
        {"Duration (minutes", {"Duration (minutes", FieldType::Int32}},
        {"Data Input Count", {"Data Input Count", FieldType::Int32}},
        {"Version Counter (autoincremented", {"Version Counter (autoincremented", FieldType::Int32}},
        {"", {"", FieldType::Int32}},
        {"Branch Count", {"Branch Count", FieldType::Int32}},
        {"PNAM", {"PNAM", FieldType::String}},
        {"ALFG", {"ALFG", FieldType::Float}},
        {"SCCM", {"SCCM", FieldType::String}},
        {"ALID", {"ALID", FieldType::String}},
        {"Stage Index", {"Stage Index", FieldType::Int32}},
        {"SCFC", {"SCFC", FieldType::String}},
        {"Male Height", {"Male Height", FieldType::Float}},
        {"Female Height", {"Female Height", FieldType::Float}},
        {"Acceleration Rate", {"Acceleration Rate", FieldType::Float}},
        {"Deceleration Rate", {"Deceleration Rate", FieldType::Float}},
        {"Aim Angle Tolerance", {"Aim Angle Tolerance", FieldType::Float}},
        {"Angular Acceleration Rate", {"Angular Acceleration Rate", FieldType::Float}},
        {"Angular Tolerance", {"Angular Tolerance", FieldType::Float}},
        {"XP Value", {"XP Value", FieldType::Int32}},
        {"Orientation Limits - Pitch", {"Orientation Limits - Pitch", FieldType::Float}},
        {"Orientation Limits - Roll", {"Orientation Limits - Roll", FieldType::Float}},
        {"Severable - Debris Scale", {"Severable - Debris Scale", FieldType::Float}},
        {"Severable - Debris Count", {"Severable - Debris Count", FieldType::Int32}},
        {"Severable - Decal Count", {"Severable - Decal Count", FieldType::Int32}},
        {"Explodable - Debris Scale", {"Explodable - Debris Scale", FieldType::Float}},
        {"Explodable - Debris Count", {"Explodable - Debris Count", FieldType::Int32}},
        {"Explodable - Decal Count", {"Explodable - Decal Count", FieldType::Int32}},
        {"NAM5", {"NAM5", FieldType::String}},
        {"NAM6", {"NAM6", FieldType::String}},
        {"NAME", {"NAME", FieldType::String}},
        {"ZNAM", {"ZNAM", FieldType::String}},
        {"FDDS", {"FDDS", FieldType::String}},
        {"BSTT", {"BSTT", FieldType::String}},
        {"HSTT", {"HSTT", FieldType::String}},
        {"FCTP", {"FCTP", FieldType::String}},
        {"FSTT", {"FSTT", FieldType::String}},
        {"SGNM", {"SGNM", FieldType::String}},
        {"SAPT", {"SAPT", FieldType::String}},
        {"PTOP", {"PTOP", FieldType::Float}},
        {"NTOP", {"NTOP", FieldType::Float}},
        {"XRDS", {"XRDS", FieldType::Float}},
        {"XHTW", {"XHTW", FieldType::Float}},
        {"XFVC", {"XFVC", FieldType::Float}},
        {"Distance (m", {"Distance (m", FieldType::Float}},
        {"Delay (s", {"Delay (s", FieldType::Float}},
        {"Unknown", {"Unknown", FieldType::Float}},
        {"XDTS", {"XDTS", FieldType::String}},
        {"Size", {"Size", FieldType::Int32}},
        {"FOV 90+/-", {"FOV 90+/-", FieldType::Float}},
        {"Luminous Scale", {"Luminous Scale", FieldType::Float}},
        {"End Distance Cap", {"End Distance Cap", FieldType::Float}},
        {"Near Clip/Cut On", {"Near Clip/Cut On", FieldType::Float}},
        {"Parent Node", {"Parent Node", FieldType::Int32}},
        {"Linked Node", {"Linked Node", FieldType::Int32}},
        {"Width Scale", {"Width Scale", FieldType::Float}},
        {"Height Scale", {"Height Scale", FieldType::Float}},
        {"Static Rotation", {"Static Rotation", FieldType::Float}},
        {"Animated Rotation Speed", {"Animated Rotation Speed", FieldType::Float}},
        {"Animated Wave Rotation Speed", {"Animated Wave Rotation Speed", FieldType::Float}},
        {"Animated Wave Rotation Amount", {"Animated Wave Rotation Amount", FieldType::Float}},
        {"Static Scale U 1.0+/-", {"Static Scale U 1.0+/-", FieldType::Float}},
        {"Static Scale V 1.0+/-", {"Static Scale V 1.0+/-", FieldType::Float}},
        {"Wave Scaling U Speed", {"Wave Scaling U Speed", FieldType::Float}},
        {"Wave Scaling V Speed", {"Wave Scaling V Speed", FieldType::Float}},
        {"Wave Scaling U Amount", {"Wave Scaling U Amount", FieldType::Float}},
        {"Wave Scaling V Amount", {"Wave Scaling V Amount", FieldType::Float}},
        {"Static Offset U", {"Static Offset U", FieldType::Float}},
        {"Static Offset V", {"Static Offset V", FieldType::Float}},
        {"Rotation Pivot U 0.5+/-", {"Rotation Pivot U 0.5+/-", FieldType::Float}},
        {"Rotation Pivot V 0.5+/-", {"Rotation Pivot V 0.5+/-", FieldType::Float}},
        {"Scroll Speed U", {"Scroll Speed U", FieldType::Float}},
        {"Scroll Speed V", {"Scroll Speed V", FieldType::Float}},
        {"Wave Scroll Speed U", {"Wave Scroll Speed U", FieldType::Float}},
        {"Wave Scroll Speed V", {"Wave Scroll Speed V", FieldType::Float}},
        {"Wave Scroll Amount U", {"Wave Scroll Amount U", FieldType::Float}},
        {"Wave Scroll Amount V", {"Wave Scroll Amount V", FieldType::Float}},
        {"Random Time Offset Range", {"Random Time Offset Range", FieldType::Float}},
        {"Collision Layer", {"Collision Layer", FieldType::Int32}},
        {"XLVD", {"XLVD", FieldType::Float}},
        {"XRFE", {"XRFE", FieldType::Float}},
        {"Right 1.0+/-", {"Right 1.0+/-", FieldType::Float}},
        {"Top 1.0+/-", {"Top 1.0+/-", FieldType::Float}},
        {"Falloff Intensity 100.0+/-", {"Falloff Intensity 100.0+/-", FieldType::Float}},
        {"XGDS", {"XGDS", FieldType::Float}},
        {"Slack", {"Slack", FieldType::Float}},
        {"Thickness", {"Thickness", FieldType::Float}},
        {"Charge Time", {"Charge Time", FieldType::Float}},
        {"Cast Duration", {"Cast Duration", FieldType::Float}},
        {"Range", {"Range", FieldType::Float}},
        {"Max Angle (30-120", {"Max Angle (30-120", FieldType::Float}},
        {"Leaf Amplitude", {"Leaf Amplitude", FieldType::Float}},
        {"Leaf Frequency", {"Leaf Frequency", FieldType::Float}},
        {"FormType", {"FormType", FieldType::Int32}},
        {"Spring", {"Spring", FieldType::Int32}},
        {"Summer ", {"Summer ", FieldType::Int32}},
        {"Fall", {"Fall", FieldType::Int32}},
        {"Winter", {"Winter", FieldType::Int32}},
        {"FMAH", {"FMAH", FieldType::Float}},
        {"FMIH", {"FMIH", FieldType::Float}},
        {"Cone of Fire - Degrees X", {"Cone of Fire - Degrees X", FieldType::Float}},
        {"Cone of Fire - Degrees Y", {"Cone of Fire - Degrees Y", FieldType::Float}},
        {"Cone of Fire - Increase Per Shot", {"Cone of Fire - Increase Per Shot", FieldType::Float}},
        {"Cone of Fire - Decrease Per Sec", {"Cone of Fire - Decrease Per Sec", FieldType::Float}},
        {"Cone of Fire - Decrease Delay in Sec", {"Cone of Fire - Decrease Delay in Sec", FieldType::Float}},
        {"Cone of Fire - Sneak Mult", {"Cone of Fire - Sneak Mult", FieldType::Float}},
        {"Recoil - Diminish Spring Force", {"Recoil - Diminish Spring Force", FieldType::Float}},
        {"Recoil - Diminish Sights Mult", {"Recoil - Diminish Sights Mult", FieldType::Float}},
        {"Recoil - Degrees Per Shot X", {"Recoil - Degrees Per Shot X", FieldType::Float}},
        {"Recoil - Degrees Per Shot Y", {"Recoil - Degrees Per Shot Y", FieldType::Float}},
        {"Recoil - Hip Mult", {"Recoil - Hip Mult", FieldType::Float}},
        {"Recoil - Shots for Runaway", {"Recoil - Shots for Runaway", FieldType::Int32}},
        {"Recoil - Arc", {"Recoil - Arc", FieldType::Float}},
        {"Recoil - Arc Rotate", {"Recoil - Arc Rotate", FieldType::Float}},
        {"Cone of Fire - Iron Sights Mult", {"Cone of Fire - Iron Sights Mult", FieldType::Float}},
        {"Recoil - Base Stability", {"Recoil - Base Stability", FieldType::Float}},
        {"Min Delay", {"Min Delay", FieldType::Float}},
        {"Max Delay", {"Max Delay", FieldType::Float}},
        {"Default Number of Tiles", {"Default Number of Tiles", FieldType::Float}},
        {"Default Number of Slices", {"Default Number of Slices", FieldType::Int32}},
        {"Wind Settings - Sensibility", {"Wind Settings - Sensibility", FieldType::Float}},
        {"Wind Settings - Flexibility", {"Wind Settings - Flexibility", FieldType::Float}},
        {"DATA", {"DATA", FieldType::FormID}},
        {"FNAM", {"FNAM", FieldType::String}},
        {"Width", {"Width", FieldType::Float}},
        {"Height", {"Height", FieldType::Float}},
        {"Position", {"Position", FieldType::Float}},
        {"Angular Fade", {"Angular Fade", FieldType::Float}},
        {"Opacity", {"Opacity", FieldType::Float}},
        {"NAM1", {"NAM1", FieldType::String}},
        {"Max Rank", {"Max Rank", FieldType::Int32}},
        {"Level Tier Scaled Offset", {"Level Tier Scaled Offset", FieldType::Int32}},
        {"Minimum Level", {"Minimum Level", FieldType::Int32}},
        {"X1", {"X1", FieldType::Float}},
        {"Y1", {"Y1", FieldType::Float}},
        {"Z1", {"Z1", FieldType::Float}},
        {"X2", {"X2", FieldType::Float}},
        {"Y2", {"Y2", FieldType::Float}},
        {"Z2", {"Z2", FieldType::Float}},
        {"STAE", {"STAE", FieldType::String}},
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}},
        {"XMRK", {"XMRK", FieldType::String}},
        {"STRV", {"STRV", FieldType::String}},
        {"Scale", {"Scale", FieldType::Float}},
        {"Zoom Min", {"Zoom Min", FieldType::Float}},
        {"Zoom Max", {"Zoom Max", FieldType::Float}},
        {"RADR", {"RADR", FieldType::Float}},
        {"WTMX", {"WTMX", FieldType::Float}},
        {"Inner Cone Angle Degrees", {"Inner Cone Angle Degrees", FieldType::Float}},
        {"Outer Cone Angle Degrees", {"Outer Cone Angle Degrees", FieldType::Float}},
        {"Steering Degrees Per Sec", {"Steering Degrees Per Sec", FieldType::Float}},
        {"Pitch Scale", {"Pitch Scale", FieldType::Float}},
        {"Inner Steering Ring", {"Inner Steering Ring", FieldType::Float}},
        {"Outer Steering Ring", {"Outer Steering Ring", FieldType::Float}},
        {"Move Follow Degrees Per Sec", {"Move Follow Degrees Per Sec", FieldType::Float}},
        {"ADS Snap Steering Mult", {"ADS Snap Steering Mult", FieldType::Float}},
        {"ADS Snap Seconds", {"ADS Snap Seconds", FieldType::Float}},
        {"ADS Snap Cone Angle Degrees", {"ADS Snap Cone Angle Degrees", FieldType::Float}},
        {"No Steering", {"No Steering", FieldType::Float}},
        {"Bullet Bending Cone Angle Degrees", {"Bullet Bending Cone Angle Degrees", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Inner Ring", {"ADS Snap Steering Mutliplier Inner Ring", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Outer Ring", {"ADS Snap Steering Mutliplier Outer Ring", FieldType::Float}},
        {"ADS Multiplier Inner Cone Angle Degrees", {"ADS Multiplier Inner Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Outer Cone Angle Degrees", {"ADS Multiplier Outer Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Inner Steering Ring", {"ADS Multiplier Inner Steering Ring", FieldType::Float}},
        {"ADS Multiplier Outer Steering Ring", {"ADS Multiplier Outer Steering Ring", FieldType::Float}},
        {"ADS Multiplier Friction", {"ADS Multiplier Friction", FieldType::Float}},
        {"ADS Multiplier Steering Degrees Per Sec", {"ADS Multiplier Steering Degrees Per Sec", FieldType::Float}},
        {"Instance ID", {"Instance ID", FieldType::Int32}},
        {"Display Case Slot", {"Display Case Slot", FieldType::Int32}},
        {"CNAM", {"CNAM", FieldType::String}},
        {"X offset", {"X offset", FieldType::Float}},
        {"Y offset", {"Y offset", FieldType::Float}},
        {"Texture Width", {"Texture Width", FieldType::Int32}},
        {"Texture Height", {"Texture Height", FieldType::Int32}},
        {"Content Width", {"Content Width", FieldType::Int32}},
        {"Content Height", {"Content Height", FieldType::Int32}},
        {"MWGT", {"MWGT", FieldType::Float}},
        {"OBSV", {"OBSV", FieldType::Float}},
        {"OCCV", {"OCCV", FieldType::Float}},
        {"Min Width", {"Min Width", FieldType::Float}},
        {"Max Width", {"Max Width", FieldType::Float}},
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Depth", {"Depth", FieldType::Float}},
        {"Cutoff Angle (Degrees", {"Cutoff Angle (Degrees", FieldType::Float}},
        {"Acelleration Deg Per Sec", {"Acelleration Deg Per Sec", FieldType::Float}},
        {"Decelleration Deg Per Sec", {"Decelleration Deg Per Sec", FieldType::Float}},
        {"Actor Target Finder Max Distance", {"Actor Target Finder Max Distance", FieldType::Float}},
        {"Max Capsule Angle For Vertical Aiming Correction Deg", {"Max Capsule Angle For Vertical Aiming Correction Deg", FieldType::Float}},
        {"Noise Offset U", {"Noise Offset U", FieldType::Float}},
        {"Noise Offset V", {"Noise Offset V", FieldType::Float}},
        {"Noise Scale U", {"Noise Scale U", FieldType::Float}},
        {"Noise Scale V ", {"Noise Scale V ", FieldType::Float}},
        {"Noise Contrast", {"Noise Contrast", FieldType::Float}},
        {"Alt Texture Coverage", {"Alt Texture Coverage", FieldType::Float}},
        {"Alternate Data Contribution Min", {"Alternate Data Contribution Min", FieldType::Float}},
        {"Alternate Data Contribution Max", {"Alternate Data Contribution Max", FieldType::Float}},
        {"Object Density", {"Object Density", FieldType::Float}},
        {"Giant", {"Giant", FieldType::Float}},
        {"Large", {"Large", FieldType::Float}},
        {"Medium", {"Medium", FieldType::Float}},
        {"Small", {"Small", FieldType::Float}},
        {"JNAM", {"JNAM", FieldType::String}},
        {"WNAM", {"WNAM", FieldType::Float}},
        {"YNAM", {"YNAM", FieldType::Float}},
        {"UNAM", {"UNAM", FieldType::Float}},
        {"TX00", {"TX00", FieldType::String}},
        {"UX00", {"UX00", FieldType::String}},
        {"VX00", {"VX00", FieldType::String}},
        {"WX00", {"WX00", FieldType::String}},
        {"XX00", {"XX00", FieldType::String}},
        {"YX00", {"YX00", FieldType::String}},
        {"TX16", {"TX16", FieldType::String}},
        {"Texture Offset U", {"Texture Offset U", FieldType::Float}},
        {"Texture Offset V", {"Texture Offset V", FieldType::Float}},
        {"Texture Scale U", {"Texture Scale U", FieldType::Float}},
        {"Texture Scale V", {"Texture Scale V", FieldType::Float}},
        {"Normal Strength", {"Normal Strength", FieldType::Float}},
        {"Slope Start", {"Slope Start", FieldType::Float}},
        {"Slope Range", {"Slope Range", FieldType::Float}},
        {"EFSD", {"EFSD", FieldType::String}},
        {"Interval (Seonds", {"Interval (Seonds", FieldType::Float}},
        {"Delay Before Sight Activation", {"Delay Before Sight Activation", FieldType::Float}},
        {"Delay Before Sight Deactivation", {"Delay Before Sight Deactivation", FieldType::Float}},
        {"Focal Point Distance", {"Focal Point Distance", FieldType::Float}},
        {"Focal Point Distance During Aiming", {"Focal Point Distance During Aiming", FieldType::Float}},
        {"Delay Between Shots", {"Delay Between Shots", FieldType::Float}},
        {"Max Laser Pointer Distance", {"Max Laser Pointer Distance", FieldType::Float}},
        {"Max Anim Distance", {"Max Anim Distance", FieldType::Float}},
        {"Inner", {"Inner", FieldType::Float}},
        {"Outer", {"Outer", FieldType::Float}},
        {"TMPP", {"TMPP", FieldType::String}},
        {"TCMP", {"TCMP", FieldType::String}},
        {"BMPP", {"BMPP", FieldType::String}},
        {"Base Vertex Color", {"Base Vertex Color", FieldType::Int32}},
        {"Entry Size", {"Entry Size", FieldType::Int32}},
        {"XEMP", {"XEMP", FieldType::String}},
        {"Axial Tilt", {"Axial Tilt", FieldType::Float}},
        {"Rotational Velocity", {"Rotational Velocity", FieldType::Float}},
        {"Mass (in Earth Masses", {"Mass (in Earth Masses", FieldType::Float}},
        {"Radius in km", {"Radius in km", FieldType::Float}},
        {"Surface Gravity", {"Surface Gravity", FieldType::Float}},
        {"Parent Planet ID", {"Parent Planet ID", FieldType::Int32}},
        {"Planet ID", {"Planet ID", FieldType::Int32}},
        {"Density", {"Density", FieldType::Float}},
        {"Heat", {"Heat", FieldType::Float}},
        {"Hydro", {"Hydro", FieldType::Float}},
        {"Inner HZ", {"Inner HZ", FieldType::Float}},
        {"Outer HZ", {"Outer HZ", FieldType::Float}},
        {"Peri. Angle", {"Peri. Angle", FieldType::Float}},
        {"Start angle in deg", {"Start angle in deg", FieldType::Float}},
        {"Year length in days", {"Year length in days", FieldType::Float}},
        {"Asteroids", {"Asteroids", FieldType::Int32}},
        {"Random Seed", {"Random Seed", FieldType::Int32}},
        {"Avg Density Frac.", {"Avg Density Frac.", FieldType::Float}},
        {"Rayleight Scattering Coefficient", {"Rayleight Scattering Coefficient", FieldType::Float}},
        {"Mie Scattering Coefficient", {"Mie Scattering Coefficient", FieldType::Float}},
        {"Noise Type", {"Noise Type", FieldType::Int32}},
        {"Terrain Height Seed", {"Terrain Height Seed", FieldType::Int32}},
        {"Terrain Max Height (m", {"Terrain Max Height (m", FieldType::Float}},
        {"TEMP", {"TEMP", FieldType::Float}},
        {"DENS", {"DENS", FieldType::Float}},
        {"PHLA", {"PHLA", FieldType::Float}},
        {"Vein Nodes Min", {"Vein Nodes Min", FieldType::Float}},
        {"Vein Nodes Max", {"Vein Nodes Max", FieldType::Float}},
        {"Node Size Min", {"Node Size Min", FieldType::Float}},
        {"Node Size Max", {"Node Size Max", FieldType::Float}},
        {"Max Angle Offset", {"Max Angle Offset", FieldType::Float}},
        {"Chance to Appear", {"Chance to Appear", FieldType::Float}},
        {"Max Node Offset", {"Max Node Offset", FieldType::Float}},
        {"Chance per Node", {"Chance per Node", FieldType::Float}},
        {"Segment Length Min", {"Segment Length Min", FieldType::Float}},
        {"Segment Length Max", {"Segment Length Max", FieldType::Float}},
        {"Surface Item Chance None", {"Surface Item Chance None", FieldType::Float}},
        {"Blobbiness", {"Blobbiness", FieldType::Float}},
        {"Required Count", {"Required Count", FieldType::Int32}},
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}},
        {"Common", {"Common", FieldType::Float}},
        {"Uncommon", {"Uncommon", FieldType::Float}},
        {"Rare", {"Rare", FieldType::Float}},
        {"Column", {"Column", FieldType::Int32}},
        {"Step", {"Step", FieldType::Float}},
        {"VORV", {"VORV", FieldType::Float}},
        {"VORN", {"VORN", FieldType::Float}},
        {"Depth Amount", {"Depth Amount", FieldType::Float}},
        {"Red", {"Red", FieldType::Float}},
        {"Green", {"Green", FieldType::Float}},
        {"Blue", {"Blue", FieldType::Float}},
        {"Phytoplankton", {"Phytoplankton", FieldType::Float}},
        {"Sediment", {"Sediment", FieldType::Float}},
        {"Yellow Matter", {"Yellow Matter", FieldType::Float}},
        {"Oceanness", {"Oceanness", FieldType::Float}},
        {"Fog Amount", {"Fog Amount", FieldType::Float}},
        {"Near Fog", {"Near Fog", FieldType::Float}},
        {"Far Fog", {"Far Fog", FieldType::Float}},
        {"Normal Magnitude", {"Normal Magnitude", FieldType::Float}},
        {"Shallow Normal Falloff", {"Shallow Normal Falloff", FieldType::Float}},
        {"Deep Normal Falloff", {"Deep Normal Falloff", FieldType::Float}},
        {"Surface Effect Falloff", {"Surface Effect Falloff", FieldType::Float}},
        {"Force", {"Force", FieldType::Float}},
        {"Velocity", {"Velocity", FieldType::Float}},
        {"Falloff", {"Falloff", FieldType::Float}},
        {"Dampener", {"Dampener", FieldType::Float}},
        {"Starting Size", {"Starting Size", FieldType::Float}},
        {"Layer 1 - Wind Direction", {"Layer 1 - Wind Direction", FieldType::Float}},
        {"Layer 2 - Wind Direction", {"Layer 2 - Wind Direction", FieldType::Float}},
        {"Layer 3 - Wind Direction", {"Layer 3 - Wind Direction", FieldType::Float}},
        {"Layer 1 - Wind Speed", {"Layer 1 - Wind Speed", FieldType::Float}},
        {"Layer 2 - Wind Speed", {"Layer 2 - Wind Speed", FieldType::Float}},
        {"Layer 3 - Wind Speed", {"Layer 3 - Wind Speed", FieldType::Float}},
        {"Layer 1 - Amplitude Scale", {"Layer 1 - Amplitude Scale", FieldType::Float}},
        {"Layer 2 - Amplitude Scale", {"Layer 2 - Amplitude Scale", FieldType::Float}},
        {"Layer 3 - Amplitude Scale", {"Layer 3 - Amplitude Scale", FieldType::Float}},
        {"Layer 1 - UV Scale", {"Layer 1 - UV Scale", FieldType::Float}},
        {"Layer 2 - UV Scale", {"Layer 2 - UV Scale", FieldType::Float}},
        {"Layer 3 - UV Scale", {"Layer 3 - UV Scale", FieldType::Float}},
        {"Layer 1 - Noise Falloff", {"Layer 1 - Noise Falloff", FieldType::Float}},
        {"Layer 2 - Noise Falloff", {"Layer 2 - Noise Falloff", FieldType::Float}},
        {"Layer 3 - Noise Falloff", {"Layer 3 - Noise Falloff", FieldType::Float}},
        {"Flowmap Scale", {"Flowmap Scale", FieldType::Float}},
        {"Roughnes", {"Roughnes", FieldType::Float}},
        {"Sighted Transition (Seconds", {"Sighted Transition (Seconds", FieldType::Float}},
        {"Accuracy Bonus", {"Accuracy Bonus", FieldType::Int32}},
        {"Ammo Capacity", {"Ammo Capacity", FieldType::Int32}},
        {"Projectiles Count", {"Projectiles Count", FieldType::Int32}},
        {"Number of Impact Sounds", {"Number of Impact Sounds", FieldType::Int32}},
        {"Heading Speed", {"Heading Speed", FieldType::Float}},
        {"Pitch Speed", {"Pitch Speed", FieldType::Float}},
        {"Accuracy", {"Accuracy", FieldType::Float}},
        {"Full Power (Seconds", {"Full Power (Seconds", FieldType::Float}},
        {"Min Power Per Shot", {"Min Power Per Shot", FieldType::Float}},
        {"Crit Charge Bonus", {"Crit Charge Bonus", FieldType::Float}},
        {"Base Damage", {"Base Damage", FieldType::Float}},
        {"Range - Min", {"Range - Min", FieldType::Float}},
        {"Range - Max", {"Range - Max", FieldType::Float}},
        {"Out of Range Damage Mult", {"Out of Range Damage Mult", FieldType::Float}},
        {"Crit Damage Mult", {"Crit Damage Mult", FieldType::Float}},
        {"Scale Control Point", {"Scale Control Point", FieldType::Float}},
        {"Crit Chance Inc Mult", {"Crit Chance Inc Mult", FieldType::Float}},
        {"Burst count", {"Burst count", FieldType::Int32}},
        {"Attack (Seconds", {"Attack (Seconds", FieldType::Float}},
        {"Fire (Seconds", {"Fire (Seconds", FieldType::Float}},
        {"Attack Delay (Seconds", {"Attack Delay (Seconds", FieldType::Float}},
        {"Bolt Charge (Seconds", {"Bolt Charge (Seconds", FieldType::Float}},
        {"Shots Per Second", {"Shots Per Second", FieldType::Float}},
        {"Weapon Attack Animation Duration", {"Weapon Attack Animation Duration", FieldType::Float}},
        {"Trigger Threshold - Primary Trigger", {"Trigger Threshold - Primary Trigger", FieldType::Float}},
        {"Trigger Threshold - Second Stage", {"Trigger Threshold - Second Stage", FieldType::Float}},
        {"Burst Delay (Seconds", {"Burst Delay (Seconds", FieldType::Float}},
        {"Base weight", {"Base weight", FieldType::Float}},
        {"Base value", {"Base value", FieldType::Int32}},
        {"Base Speed", {"Base Speed", FieldType::Float}},
        {"Attack Oxygen Cost", {"Attack Oxygen Cost", FieldType::Float}},
        {"Bash Damage", {"Bash Damage", FieldType::Float}},
        {"Reach", {"Reach", FieldType::Float}},
        {"Recharge time", {"Recharge time", FieldType::Float}},
        {"Recharge delay", {"Recharge delay", FieldType::Float}},
        {"Variable Power Transition Duration", {"Variable Power Transition Duration", FieldType::Float}},
        {"Power Damage Multiplier", {"Power Damage Multiplier", FieldType::Float}},
        {"Reload Seconds", {"Reload Seconds", FieldType::Float}},
        {"Reload Speed", {"Reload Speed", FieldType::Float}},
        {"Value - Min", {"Value - Min", FieldType::Float}},
        {"Value - Max", {"Value - Max", FieldType::Float}},
        {"Input - Min", {"Input - Min", FieldType::Float}},
        {"Input - Max", {"Input - Max", FieldType::Float}},
        {"MOD4", {"MOD4", FieldType::String}},
        {"MO4S", {"MO4S", FieldType::Float}},
        {"Color Remapping Index", {"Color Remapping Index", FieldType::Float}},
        {"Attack Action Point Cost", {"Attack Action Point Cost", FieldType::Float}},
        {"Firing Camera Shake Intensity", {"Firing Camera Shake Intensity", FieldType::Float}},
        {"Firing Camera Shake Duration", {"Firing Camera Shake Duration", FieldType::Float}},
        {"AI Firing Arc", {"AI Firing Arc", FieldType::Float}},
        {"Distance From Wall", {"Distance From Wall", FieldType::Float}},
        {"GunUp to GunDown Transition Duration (s", {"GunUp to GunDown Transition Duration (s", FieldType::Float}},
        {"GunDown to GunUp Transition Duration (s", {"GunDown to GunUp Transition Duration (s", FieldType::Float}},
        {"Wind Speed", {"Wind Speed", FieldType::Int32}},
        {"Trans Delta", {"Trans Delta", FieldType::Int32}},
        {"Sun Glare", {"Sun Glare", FieldType::Int32}},
        {"Sun Damage", {"Sun Damage", FieldType::Int32}},
        {"Precipitation - Begin Fade In", {"Precipitation - Begin Fade In", FieldType::Int32}},
        {"Precipitation - End Fade Out", {"Precipitation - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Begin Fade In", {"Thunder/Lightning - Begin Fade In", FieldType::Int32}},
        {"Thunder/Lightning - End Fade Out", {"Thunder/Lightning - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Frequency", {"Thunder/Lightning - Frequency", FieldType::Int32}},
        {"Visual Effect - Begin", {"Visual Effect - Begin", FieldType::Int32}},
        {"Visual Effect - End", {"Visual Effect - End", FieldType::Int32}},
        {"Wind Direction", {"Wind Direction", FieldType::Int32}},
        {"Wind Direction Range", {"Wind Direction Range", FieldType::Int32}},
        {"Wind Turbulance", {"Wind Turbulance", FieldType::Int32}},
        {"NAM7", {"NAM7", FieldType::String}},
        {"NAMA", {"NAMA", FieldType::Float}},
        {"XWEM", {"XWEM", FieldType::String}},
        {"FOV Mult", {"FOV Mult", FieldType::Float}},
        {"FOV Offset", {"FOV Offset", FieldType::Float}},
        {"Offset Duration", {"Offset Duration", FieldType::Float}}
    }}},
    {"LENS", {"'Lens Flare'", {
        {"DNAM", {"DNAM", FieldType::String}},
        {"FNAM", {"FNAM", FieldType::String}},
        {"Width", {"Width", FieldType::Float}},
        {"Height", {"Height", FieldType::Float}},
        {"Position", {"Position", FieldType::Float}},
        {"Angular Fade", {"Angular Fade", FieldType::Float}},
        {"Opacity", {"Opacity", FieldType::Float}}
    }}},
    {"LFSD", {"Lens Flare Data", {
        {"Width", {"Width", FieldType::Float}},
        {"Height", {"Height", FieldType::Float}},
        {"Position", {"Position", FieldType::Float}},
        {"Angular Fade", {"Angular Fade", FieldType::Float}},
        {"Opacity", {"Opacity", FieldType::Float}}
    }}},
    {"LGDI", {"'Legendary Item'", {

    }}},
    {"LGTM", {"'Lighting Template'", {
        {"Fog Near", {"Fog Near", FieldType::Float}},
        {"Fog Far", {"Fog Far", FieldType::Float}},
        {"Directional Rotation XY", {"Directional Rotation XY", FieldType::Int32}},
        {"Directional Rotation Z", {"Directional Rotation Z", FieldType::Int32}},
        {"Directional Fade", {"Directional Fade", FieldType::Float}},
        {"Fog Clip Distance", {"Fog Clip Distance", FieldType::Float}},
        {"Fog Power", {"Fog Power", FieldType::Float}},
        {"Light Fade Distance Start", {"Light Fade Distance Start", FieldType::Float}},
        {"Light Fade Distance Stop", {"Light Fade Distance Stop", FieldType::Float}},
        {"Height Mid", {"Height Mid", FieldType::Float}},
        {"Height Range", {"Height Range", FieldType::Float}},
        {"High Density Scale", {"High Density Scale", FieldType::Float}},
        {"Fog Near Scale", {"Fog Near Scale", FieldType::Float}},
        {"Fog Far Scale", {"Fog Far Scale", FieldType::Float}},
        {"High Near Scale", {"High Near Scale", FieldType::Float}},
        {"High Far Scale", {"High Far Scale", FieldType::Float}},
        {"Far Height Mid", {"Far Height Mid", FieldType::Float}},
        {"Far Height Range", {"Far Height Range", FieldType::Float}}
    }}},
    {"LIGH", {"'Light'", {
        {"Time", {"Time", FieldType::Int32}},
        {"Radius", {"Radius", FieldType::Float}},
        {"Falloff Exponent", {"Falloff Exponent", FieldType::Float}},
        {"FOV", {"FOV", FieldType::Float}},
        {"Near Clip", {"Near Clip", FieldType::Float}},
        {"Period", {"Period", FieldType::Float}},
        {"Intensity Amplitude", {"Intensity Amplitude", FieldType::Float}},
        {"Movement Amplitude", {"Movement Amplitude", FieldType::Float}},
        {"Shadow Offset", {"Shadow Offset", FieldType::Float}},
        {"Inner FOV", {"Inner FOV", FieldType::Float}},
        {"PBR - Light Temperature (K", {"PBR - Light Temperature (K", FieldType::Int32}},
        {"PBR - Luminous Power (lm", {"PBR - Luminous Power (lm", FieldType::Int32}},
        {"Adaptive Light Ec", {"Adaptive Light Ec", FieldType::Float}},
        {"Adaptive Light Ev 100 Min", {"Adaptive Light Ev 100 Min", FieldType::Float}},
        {"Adaptive Light Ev 100 Max", {"Adaptive Light Ev 100 Max", FieldType::Float}},
        {"Radius Falloff Exponent", {"Radius Falloff Exponent", FieldType::Float}},
        {"NAM0", {"NAM0", FieldType::String}},
        {"Left", {"Left", FieldType::Float}},
        {"Bottom", {"Bottom", FieldType::Float}},
        {"Right", {"Right", FieldType::Float}},
        {"Top", {"Top", FieldType::Float}},
        {"Falloff Intensity", {"Falloff Intensity", FieldType::Float}},
        {"FVLD", {"FVLD", FieldType::Float}}
    }}},
    {"LMSW", {"'Layered Material Swap'", {

    }}},
    {"LSCR", {"'Load Screen'", {
        {"ICON", {"ICON", FieldType::String}},
        {"Min", {"Min", FieldType::Int32}},
        {"Max", {"Max", FieldType::Int32}}
    }}},
    {"LTEX", {"'Landscape Texture'", {
        {"BNAM", {"BNAM", FieldType::String}},
        {"Friction", {"Friction", FieldType::Int32}},
        {"Restitution", {"Restitution", FieldType::Int32}}
    }}},
    {"LVLB", {"'Leveled Base Form'", {

    }}},
    {"LVLI", {"'Leveled Item'", {

    }}},
    {"LVLN", {"'Leveled NPC'", {

    }}},
    {"LVLP", {"'Leveled Pack In'", {

    }}},
    {"LVSC", {"'Leveled Space Cell'", {

    }}},
    {"LVSP", {"'Leveled Spell'", {

    }}},
    {"MAAM", {"'Melee Aim Assist Model'", {
        {"Inner Cone Angle Degrees", {"Inner Cone Angle Degrees", FieldType::Float}},
        {"Outer Cone Angle Degrees", {"Outer Cone Angle Degrees", FieldType::Float}},
        {"Steering Degrees Per Sec", {"Steering Degrees Per Sec", FieldType::Float}},
        {"Acelleration Deg Per Sec", {"Acelleration Deg Per Sec", FieldType::Float}},
        {"Decelleration Deg Per Sec", {"Decelleration Deg Per Sec", FieldType::Float}},
        {"Actor Target Finder Max Distance", {"Actor Target Finder Max Distance", FieldType::Float}},
        {"Max Capsule Angle For Vertical Aiming Correction Deg", {"Max Capsule Angle For Vertical Aiming Correction Deg", FieldType::Float}}
    }}},
    {"MATT", {"'Material Type'", {
        {"MNAM", {"MNAM", FieldType::String}},
        {"BNAM", {"BNAM", FieldType::Float}},
        {"ANAM", {"ANAM", FieldType::String}}
    }}},
    {"MESG", {"'Message'", {
        {"SNAM", {"SNAM", FieldType::String}}
    }}},
    {"MGEF", {"'Magic Effect'", {

    }}},
    {"MISC", {"'Misc. Item'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}}
    }}},
    {"MOBC", {"Base Vertex Color", {
        {"Base Vertex Color", {"Base Vertex Color", FieldType::Int32}}
    }}},
    {"MOVT", {"'Movement Type'", {
        {"MNAM", {"MNAM", FieldType::String}},
        {"LNAM", {"LNAM", FieldType::Float}},
        {"KNAM", {"KNAM", FieldType::Float}}
    }}},
    {"MRPH", {"'Morphable Object'", {
        {"TMPP", {"TMPP", FieldType::String}},
        {"TCMP", {"TCMP", FieldType::String}},
        {"BMPP", {"BMPP", FieldType::String}},
        {"Base Vertex Color", {"Base Vertex Color", FieldType::Int32}}
    }}},
    {"MRSV", {"Body Morph Region Values", {
        {"Head", {"Head", FieldType::Float}},
        {"Upper Torso", {"Upper Torso", FieldType::Float}},
        {"Arms", {"Arms", FieldType::Float}},
        {"Lower Torso", {"Lower Torso", FieldType::Float}},
        {"Legs", {"Legs", FieldType::Float}}
    }}},
    {"MSTT", {"'Moveable Static'", {
        {"MSMO", {"MSMO", FieldType::Float}}
    }}},
    {"MTPT", {"'Material Path'", {

    }}},
    {"MUSC", {"'Music Type'", {
        {"Priority", {"Priority", FieldType::Int32}},
        {"Ducking (dB", {"Ducking (dB", FieldType::Int32}}
    }}},
    {"MUST", {"'Music Track'", {
        {"FLTV", {"FLTV", FieldType::Float}},
        {"DNAM", {"DNAM", FieldType::Float}},
        {"Point", {"Point", FieldType::Float}}
    }}},
    {"MWGT", {"Weight", {
        {"Thin", {"Thin", FieldType::Float}},
        {"Muscular", {"Muscular", FieldType::Float}},
        {"Fat", {"Fat", FieldType::Float}}
    }}},
    {"NAM2", {"Cell Min", {
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}}
    }}},
    {"NAM3", {"Cell Max", {
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}}
    }}},
    {"NAM4", {"Height Range", {
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}}
    }}},
    {"NAVI", {"'Navmesh Info Map'", {
        {"Preferred %", {"Preferred %", FieldType::Float}},
        {"Vertex 0", {"Vertex 0", FieldType::Int32}},
        {"Vertex 1", {"Vertex 1", FieldType::Int32}},
        {"Vertex 2", {"Vertex 2", FieldType::Int32}},
        {"Grid Y", {"Grid Y", FieldType::Int32}},
        {"Grid X", {"Grid X", FieldType::Int32}},
        {"Index", {"Index", FieldType::Int32}}
    }}},
    {"NAVM", {"'Navmesh'", {
        {"Reference", {"Reference", FieldType::FormID}},
        {"Triangle", {"Triangle", FieldType::Int32}}
    }}},
    {"NOCM", {"'Navmesh Obstacle Cover Manager'", {
        {"NAM1", {"NAM1", FieldType::String}}
    }}},
    {"NOTE", {"'Note'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}},
        {"PNAM", {"PNAM", FieldType::String}}
    }}},
    {"NPC_", {"'Non-Player Character'", {
        {"XP Value Offset", {"XP Value Offset", FieldType::Int32}},
        {"Level", {"Level", FieldType::Int32}},
        {"Calc min level", {"Calc min level", FieldType::Int32}},
        {"Calc max level", {"Calc max level", FieldType::Int32}},
        {"Disposition Base", {"Disposition Base", FieldType::Int32}},
        {"Rank", {"Rank", FieldType::Int32}},
        {"Max Number Of Times To React", {"Max Number Of Times To React", FieldType::Float}},
        {"Reaction Radius", {"Reaction Radius", FieldType::Float}},
        {"Exit Radius", {"Exit Radius", FieldType::Float}},
        {"Max Herd Members To Animate", {"Max Herd Members To Animate", FieldType::Float}},
        {"Number of Warnings Before Attack", {"Number of Warnings Before Attack", FieldType::Float}},
        {"Warn Timer On Warn/Attack", {"Warn Timer On Warn/Attack", FieldType::Float}},
        {"Cool Down Timer", {"Cool Down Timer", FieldType::Float}},
        {"Flee Distance GLOB", {"Flee Distance GLOB", FieldType::FormID}},
        {"Safe Timer GLOB", {"Safe Timer GLOB", FieldType::FormID}},
        {"Chance of Diversion Animation GLOB", {"Chance of Diversion Animation GLOB", FieldType::FormID}},
        {"Flee Distance", {"Flee Distance", FieldType::Float}},
        {"Safe Timer", {"Safe Timer", FieldType::Float}},
        {"Chance of Diversion Animation", {"Chance of Diversion Animation", FieldType::Float}},
        {"Calculated Health", {"Calculated Health", FieldType::Int32}},
        {"Calculated Action Points", {"Calculated Action Points", FieldType::Int32}},
        {"Far Away Model Distance", {"Far Away Model Distance", FieldType::Int32}},
        {"Geared Up Weapons", {"Geared Up Weapons", FieldType::Int32}},
        {"NAM4", {"NAM4", FieldType::Float}},
        {"Thin", {"Thin", FieldType::Float}},
        {"Muscular", {"Muscular", FieldType::Float}},
        {"Fat", {"Fat", FieldType::Float}},
        {"TNAM", {"TNAM", FieldType::String}},
        {"QNAM", {"QNAM", FieldType::String}},
        {"VNAM", {"VNAM", FieldType::String}},
        {"Head", {"Head", FieldType::Float}},
        {"Upper Torso", {"Upper Torso", FieldType::Float}},
        {"Arms", {"Arms", FieldType::Float}},
        {"Lower Torso", {"Lower Torso", FieldType::Float}},
        {"Legs", {"Legs", FieldType::Float}},
        {"FMRS", {"FMRS", FieldType::Float}},
        {"FMRG", {"FMRG", FieldType::String}},
        {"BMPN", {"BMPN", FieldType::String}},
        {"BMPV", {"BMPV", FieldType::Float}},
        {"HCOL", {"HCOL", FieldType::String}},
        {"FHCL", {"FHCL", FieldType::String}},
        {"BCOL", {"BCOL", FieldType::String}},
        {"ECOL", {"ECOL", FieldType::String}},
        {"JCOL", {"JCOL", FieldType::String}},
        {"TETC", {"TETC", FieldType::String}},
        {"Acceleration (m", {"Acceleration (m", FieldType::Float}},
        {"Deceleration (m", {"Deceleration (m", FieldType::Float}},
        {"Angular Acceleration (deg", {"Angular Acceleration (deg", FieldType::Float}},
        {"Angular Tolerance (deg", {"Angular Tolerance (deg", FieldType::Float}},
        {"Flight Radius", {"Flight Radius", FieldType::Float}},
        {"Injured Health Pct", {"Injured Health Pct", FieldType::Float}},
        {"Health %", {"Health %", FieldType::Float}},
        {"Chance", {"Chance", FieldType::Float}},
        {"Recover Chance", {"Recover Chance", FieldType::Float}},
        {"Time Min", {"Time Min", FieldType::Float}},
        {"Time Max", {"Time Max", FieldType::Float}},
        {"Health Drain Rate", {"Health Drain Rate", FieldType::Float}},
        {"Debris Scale", {"Debris Scale", FieldType::Float}},
        {"Debris Count", {"Debris Count", FieldType::Int32}},
        {"Decal Count", {"Decal Count", FieldType::Int32}},
        {"Recover Chance On Damage Received", {"Recover Chance On Damage Received", FieldType::Float}},
        {"Health After Recovery", {"Health After Recovery", FieldType::Float}},
        {"Immunity Duration After Recovery", {"Immunity Duration After Recovery", FieldType::Float}}
    }}},
    {"NVNM", {"Navmesh Geometry", {
        {"Version", {"Version", FieldType::Int32}}
    }}},
    {"OBTS", {"Object Mod Template Item", {
        {"Level Min", {"Level Min", FieldType::Int32}},
        {"Level Max", {"Level Max", FieldType::Int32}},
        {"Parent Combination Index", {"Parent Combination Index", FieldType::Int32}}
    }}},
    {"OMOD", {"'Object Modification'", {
        {"Max Rank", {"Max Rank", FieldType::Int32}},
        {"Level Tier Scaled Offset", {"Level Tier Scaled Offset", FieldType::Int32}},
        {"Minimum Level", {"Minimum Level", FieldType::Int32}}
    }}},
    {"ONAM", {"Rotation", {
        {"Min", {"Min", FieldType::Int32}},
        {"Max", {"Max", FieldType::Int32}}
    }}},
    {"OSWP", {"'Object Swap'", {
        {"KNAM", {"KNAM", FieldType::FormID}},
        {"VNAM", {"VNAM", FieldType::FormID}}
    }}},
    {"OTFT", {"'Outfit'", {

    }}},
    {"OVIS", {"'Object Visibility Manager'", {
        {"X1", {"X1", FieldType::Float}},
        {"Y1", {"Y1", FieldType::Float}},
        {"Z1", {"Z1", FieldType::Float}},
        {"X2", {"X2", FieldType::Float}},
        {"Y2", {"Y2", FieldType::Float}},
        {"Z2", {"Z2", FieldType::Float}}
    }}},
    {"PACK", {"'Package'", {
        {"Month", {"Month", FieldType::Int32}},
        {"Date", {"Date", FieldType::Int32}},
        {"Minute", {"Minute", FieldType::Int32}},
        {"Duration (minutes", {"Duration (minutes", FieldType::Int32}},
        {"Data Input Count", {"Data Input Count", FieldType::Int32}},
        {"Version Counter (autoincremented", {"Version Counter (autoincremented", FieldType::Int32}},
        {"ANAM", {"ANAM", FieldType::String}},
        {"", {"", FieldType::Int32}},
        {"NNAM", {"NNAM", FieldType::String}},
        {"Branch Count", {"Branch Count", FieldType::Int32}},
        {"PNAM", {"PNAM", FieldType::String}}
    }}},
    {"PCBN", {"'Planet Content Manager Branch Node'", {

    }}},
    {"PCCN", {"'Planet Content Manager Content Node'", {

    }}},
    {"PCMT", {"'Planet Content Manager Tree'", {

    }}},
    {"PDCL", {"'Projected Decal'", {
        {"Min Width", {"Min Width", FieldType::Float}},
        {"Max Width", {"Max Width", FieldType::Float}},
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Depth", {"Depth", FieldType::Float}},
        {"Cutoff Angle (Degrees", {"Cutoff Angle (Degrees", FieldType::Float}}
    }}},
    {"PERK", {"'Perk'", {
        {"GNAM", {"GNAM", FieldType::String}},
        {"ICON", {"ICON", FieldType::String}},
        {"FNAM", {"FNAM", FieldType::String}}
    }}},
    {"PERS", {"'Unknown'", {
        {"Unknown", {"Unknown", FieldType::FormID}}
    }}},
    {"PFPC", {"Ingredient Production", {
        {"Spring", {"Spring", FieldType::Int32}},
        {"Summer ", {"Summer ", FieldType::Int32}},
        {"Fall", {"Fall", FieldType::Int32}},
        {"Winter", {"Winter", FieldType::Int32}}
    }}},
    {"PKCU", {"Counter", {
        {"Data Input Count", {"Data Input Count", FieldType::Int32}}
    }}},
    {"PKIN", {"'Pack-In'", {

    }}},
    {"PLYR", {"'Player Reference'", {

    }}},
    {"PMFT", {"'Photo Mode Feature'", {
        {"X offset", {"X offset", FieldType::Float}},
        {"Y offset", {"Y offset", FieldType::Float}},
        {"Texture Width", {"Texture Width", FieldType::Int32}},
        {"Texture Height", {"Texture Height", FieldType::Int32}},
        {"Content Width", {"Content Width", FieldType::Int32}},
        {"Content Height", {"Content Height", FieldType::Int32}},
        {"HNAM", {"HNAM", FieldType::String}}
    }}},
    {"PNAM", {"Data", {
        {"Priority", {"Priority", FieldType::Int32}},
        {"Ducking (dB", {"Ducking (dB", FieldType::Int32}}
    }}},
    {"PNDT", {"'Planet'", {
        {"Chance", {"Chance", FieldType::Float}},
        {"Entry Size", {"Entry Size", FieldType::Int32}},
        {"Frequency", {"Frequency", FieldType::Int32}},
        {"GNAM", {"GNAM", FieldType::Float}},
        {"XEMP", {"XEMP", FieldType::String}},
        {"Axial Tilt", {"Axial Tilt", FieldType::Float}},
        {"Rotational Velocity", {"Rotational Velocity", FieldType::Float}},
        {"Mass (in Earth Masses", {"Mass (in Earth Masses", FieldType::Float}},
        {"Radius in km", {"Radius in km", FieldType::Float}},
        {"Surface Gravity", {"Surface Gravity", FieldType::Float}},
        {"Parent Planet ID", {"Parent Planet ID", FieldType::Int32}},
        {"Planet ID", {"Planet ID", FieldType::Int32}},
        {"Density", {"Density", FieldType::Float}},
        {"Heat", {"Heat", FieldType::Float}},
        {"Hydro", {"Hydro", FieldType::Float}},
        {"Inner HZ", {"Inner HZ", FieldType::Float}},
        {"Outer HZ", {"Outer HZ", FieldType::Float}},
        {"Peri. Angle", {"Peri. Angle", FieldType::Float}},
        {"Start angle in deg", {"Start angle in deg", FieldType::Float}},
        {"Year length in days", {"Year length in days", FieldType::Float}},
        {"Asteroids", {"Asteroids", FieldType::Int32}},
        {"Random Seed", {"Random Seed", FieldType::Int32}},
        {"Avg Density Frac.", {"Avg Density Frac.", FieldType::Float}},
        {"Rayleight Scattering Coefficient", {"Rayleight Scattering Coefficient", FieldType::Float}},
        {"Mie Scattering Coefficient", {"Mie Scattering Coefficient", FieldType::Float}},
        {"Noise Type", {"Noise Type", FieldType::Int32}},
        {"Terrain Height Seed", {"Terrain Height Seed", FieldType::Int32}},
        {"Terrain Max Height (m", {"Terrain Max Height (m", FieldType::Float}},
        {"TEMP", {"TEMP", FieldType::Float}},
        {"DENS", {"DENS", FieldType::Float}},
        {"PHLA", {"PHLA", FieldType::Float}}
    }}},
    {"PRCB", {"Root", {
        {"Branch Count", {"Branch Count", FieldType::Int32}}
    }}},
    {"PROJ", {"'Projectile'", {
        {"Gravity", {"Gravity", FieldType::Float}},
        {"Speed", {"Speed", FieldType::Float}},
        {"Range", {"Range", FieldType::Float}},
        {"Explosion - Proximity", {"Explosion - Proximity", FieldType::Float}},
        {"Explosion - Timer", {"Explosion - Timer", FieldType::Float}},
        {"Muzzle Flash - Duration", {"Muzzle Flash - Duration", FieldType::Float}},
        {"Fade Duration", {"Fade Duration", FieldType::Float}},
        {"Impact Force", {"Impact Force", FieldType::Float}},
        {"Cone Spread", {"Cone Spread", FieldType::Float}},
        {"Collision Radius", {"Collision Radius", FieldType::Float}},
        {"Lifetime", {"Lifetime", FieldType::Float}},
        {"Relaunch Interval", {"Relaunch Interval", FieldType::Float}},
        {"Tracer Frequency", {"Tracer Frequency", FieldType::Int32}},
        {"Seek Strength", {"Seek Strength", FieldType::Float}},
        {"Tracer Speed", {"Tracer Speed", FieldType::Float}},
        {"ZeroG Recoil Strength", {"ZeroG Recoil Strength", FieldType::Float}},
        {"ZeroG Recoil Length", {"ZeroG Recoil Length", FieldType::Float}},
        {"Explosion - Delay Before Removal", {"Explosion - Delay Before Removal", FieldType::Float}},
        {"NAM1", {"NAM1", FieldType::String}}
    }}},
    {"PSDC", {"'Particle System Define Collection'", {

    }}},
    {"PSDT", {"Schedule", {
        {"Month", {"Month", FieldType::Int32}}
    }}},
    {"PTST", {"'Surface Pattern Style'", {

    }}},
    {"QRRD", {"Item", {
        {"Count", {"Count", FieldType::Int32}}
    }}},
    {"QUST", {"'Quest'", {
        {"Priority", {"Priority", FieldType::Int32}},
        {"NAM3", {"NAM3", FieldType::String}},
        {"Stage Index", {"Stage Index", FieldType::Int32}},
        {"NAM2", {"NAM2", FieldType::String}},
        {"SCFC", {"SCFC", FieldType::String}},
        {"Count", {"Count", FieldType::Int32}},
        {"SNAM", {"SNAM", FieldType::String}},
        {"SCCM", {"SCCM", FieldType::String}}
    }}},
    {"RACE", {"'Race'", {
        {"Male Height", {"Male Height", FieldType::Float}},
        {"Female Height", {"Female Height", FieldType::Float}},
        {"Thin", {"Thin", FieldType::Float}},
        {"Muscular", {"Muscular", FieldType::Float}},
        {"Fat", {"Fat", FieldType::Float}},
        {"Acceleration Rate", {"Acceleration Rate", FieldType::Float}},
        {"Deceleration Rate", {"Deceleration Rate", FieldType::Float}},
        {"Injured Health Pct", {"Injured Health Pct", FieldType::Float}},
        {"Aim Angle Tolerance", {"Aim Angle Tolerance", FieldType::Float}},
        {"Flight Radius", {"Flight Radius", FieldType::Float}},
        {"Angular Acceleration Rate", {"Angular Acceleration Rate", FieldType::Float}},
        {"Angular Tolerance", {"Angular Tolerance", FieldType::Float}},
        {"XP Value", {"XP Value", FieldType::Int32}},
        {"Debris Scale", {"Debris Scale", FieldType::Float}},
        {"Debris Count", {"Debris Count", FieldType::Int32}},
        {"Decal Count", {"Decal Count", FieldType::Int32}},
        {"Orientation Limits - Pitch", {"Orientation Limits - Pitch", FieldType::Float}},
        {"Orientation Limits - Roll", {"Orientation Limits - Roll", FieldType::Float}},
        {"Health %", {"Health %", FieldType::Float}},
        {"Chance", {"Chance", FieldType::Float}},
        {"Recover Chance", {"Recover Chance", FieldType::Float}},
        {"Time Min", {"Time Min", FieldType::Float}},
        {"Time Max", {"Time Max", FieldType::Float}},
        {"Health Drain Rate", {"Health Drain Rate", FieldType::Float}},
        {"Recover Chance On Damage Received", {"Recover Chance On Damage Received", FieldType::Float}},
        {"Health After Recovery", {"Health After Recovery", FieldType::Float}},
        {"Immunity Duration After Recovery", {"Immunity Duration After Recovery", FieldType::Float}},
        {"Severable - Debris Scale", {"Severable - Debris Scale", FieldType::Float}},
        {"Severable - Debris Count", {"Severable - Debris Count", FieldType::Int32}},
        {"Severable - Decal Count", {"Severable - Decal Count", FieldType::Int32}},
        {"Explodable - Debris Scale", {"Explodable - Debris Scale", FieldType::Float}},
        {"Explodable - Debris Count", {"Explodable - Debris Count", FieldType::Int32}},
        {"Explodable - Decal Count", {"Explodable - Decal Count", FieldType::Int32}},
        {"ANAM", {"ANAM", FieldType::String}},
        {"NAM5", {"NAM5", FieldType::String}},
        {"NAM6", {"NAM6", FieldType::String}},
        {"DNAM", {"DNAM", FieldType::String}},
        {"NAME", {"NAME", FieldType::String}},
        {"ZNAM", {"ZNAM", FieldType::String}},
        {"FDDS", {"FDDS", FieldType::String}},
        {"BSTT", {"BSTT", FieldType::String}},
        {"HSTT", {"HSTT", FieldType::String}},
        {"FCTP", {"FCTP", FieldType::String}},
        {"FSTT", {"FSTT", FieldType::String}},
        {"SGNM", {"SGNM", FieldType::String}},
        {"SAPT", {"SAPT", FieldType::String}},
        {"PTOP", {"PTOP", FieldType::Float}},
        {"NTOP", {"NTOP", FieldType::Float}}
    }}},
    {"RADR", {"Radio Receiver", {
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}}
    }}},
    {"REGN", {"'Region'", {
        {"Priority", {"Priority", FieldType::Int32}},
        {"Chance", {"Chance", FieldType::Int32}}
    }}},
    {"RELA", {"'Relationship'", {

    }}},
    {"REVB", {"'Reverb Parameters'", {

    }}},
    {"RFGP", {"'Reference Group'", {
        {"NNAM", {"NNAM", FieldType::String}}
    }}},
    {"RGDL", {"'RGDL'", {

    }}},
    {"RSGD", {"'Resource Generation Data'", {

    }}},
    {"RSPJ", {"'Research Project'", {
        {"Required Count", {"Required Count", FieldType::Int32}},
        {"Rank", {"Rank", FieldType::Int32}},
        {"CNAM", {"CNAM", FieldType::FormID}},
        {"SNAM", {"SNAM", FieldType::Float}}
    }}},
    {"SCCO", {"'Scene Collection'", {
        {"Unknown", {"Unknown", FieldType::Int32}}
    }}},
    {"SCEN", {"'Scene'", {
        {"NAM0", {"NAM0", FieldType::String}},
        {"On Start", {"On Start", FieldType::Int32}},
        {"On Completion", {"On Completion", FieldType::Int32}},
        {"SNOT", {"SNOT", FieldType::String}},
        {"DMAX", {"DMAX", FieldType::Float}},
        {"DMIN", {"DMIN", FieldType::Float}},
        {"SNAM", {"SNAM", FieldType::Float}},
        {"TNAM", {"TNAM", FieldType::Float}},
        {"PAPN", {"PAPN", FieldType::String}},
        {"SSPN", {"SSPN", FieldType::String}},
        {"HNAM", {"HNAM", FieldType::Float}},
        {"VCLR", {"VCLR", FieldType::Float}},
        {"VNML", {"VNML", FieldType::Float}},
        {"LVCR", {"LVCR", FieldType::Float}},
        {"BTXT", {"BTXT", FieldType::Float}},
        {"On Begin", {"On Begin", FieldType::Int32}},
        {"On End", {"On End", FieldType::Int32}},
        {"NNAM", {"NNAM", FieldType::String}}
    }}},
    {"SCOL", {"'Static Collection'", {

    }}},
    {"SCQS", {"Set Parent Quest Stage", {
        {"On Start", {"On Start", FieldType::Int32}},
        {"On Completion", {"On Completion", FieldType::Int32}}
    }}},
    {"SCRL", {"'Scroll'", {
        {"Value", {"Value", FieldType::Int32}},
        {"Weight", {"Weight", FieldType::Float}}
    }}},
    {"SDLT", {"'Secondary Damage List'", {

    }}},
    {"SECH", {"'Sound Echo Marker'", {
        {"NNAM", {"NNAM", FieldType::String}},
        {"BNAM", {"BNAM", FieldType::Float}}
    }}},
    {"SFBK", {"'Surface Block'", {
        {"ANAM", {"ANAM", FieldType::String}},
        {"X", {"X", FieldType::Int32}},
        {"Y", {"Y", FieldType::Int32}},
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}},
        {"Unknown", {"Unknown", FieldType::Int32}},
        {"NAM0", {"NAM0", FieldType::String}},
        {"NAM1", {"NAM1", FieldType::String}}
    }}},
    {"SFPC", {"'Surface Pattern Config'", {
        {"BNAM", {"BNAM", FieldType::String}},
        {"CNAM", {"CNAM", FieldType::Float}},
        {"Common", {"Common", FieldType::Float}},
        {"Uncommon", {"Uncommon", FieldType::Float}},
        {"Rare", {"Rare", FieldType::Float}}
    }}},
    {"SFPT", {"'Surface Pattern'", {
        {"Column", {"Column", FieldType::Int32}}
    }}},
    {"SFTR", {"'Surface Tree'", {
        {"NAM1", {"NAM1", FieldType::String}}
    }}},
    {"SHOU", {"'Shout'", {

    }}},
    {"SHWB", {"Ship Weapon Binding", {
        {"Weapon Slot 1", {"Weapon Slot 1", FieldType::Int32}},
        {"Weapon Slot 2", {"Weapon Slot 2", FieldType::Int32}},
        {"Weapon Slot 3", {"Weapon Slot 3", FieldType::Int32}}
    }}},
    {"SMBN", {"'Story Manager Branch Node'", {

    }}},
    {"SMEN", {"'Story Manager Event Node'", {

    }}},
    {"SMQN", {"'Story Manager Quest Node'", {
        {"HNAM", {"HNAM", FieldType::Float}}
    }}},
    {"SNAM", {"Data", {
        {"Inner Cone Angle Degrees", {"Inner Cone Angle Degrees", FieldType::Float}},
        {"Outer Cone Angle Degrees", {"Outer Cone Angle Degrees", FieldType::Float}},
        {"Steering Degrees Per Sec", {"Steering Degrees Per Sec", FieldType::Float}},
        {"Pitch Scale", {"Pitch Scale", FieldType::Float}},
        {"Inner Steering Ring", {"Inner Steering Ring", FieldType::Float}},
        {"Outer Steering Ring", {"Outer Steering Ring", FieldType::Float}},
        {"Friction", {"Friction", FieldType::Float}},
        {"Move Follow Degrees Per Sec", {"Move Follow Degrees Per Sec", FieldType::Float}},
        {"ADS Snap Steering Mult", {"ADS Snap Steering Mult", FieldType::Float}},
        {"ADS Snap Seconds", {"ADS Snap Seconds", FieldType::Float}},
        {"ADS Snap Cone Angle Degrees", {"ADS Snap Cone Angle Degrees", FieldType::Float}},
        {"No Steering", {"No Steering", FieldType::Float}},
        {"Bullet Bending Cone Angle Degrees", {"Bullet Bending Cone Angle Degrees", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Inner Ring", {"ADS Snap Steering Mutliplier Inner Ring", FieldType::Float}},
        {"ADS Snap Steering Mutliplier Outer Ring", {"ADS Snap Steering Mutliplier Outer Ring", FieldType::Float}},
        {"ADS Multiplier Inner Cone Angle Degrees", {"ADS Multiplier Inner Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Outer Cone Angle Degrees", {"ADS Multiplier Outer Cone Angle Degrees", FieldType::Float}},
        {"ADS Multiplier Inner Steering Ring", {"ADS Multiplier Inner Steering Ring", FieldType::Float}},
        {"ADS Multiplier Outer Steering Ring", {"ADS Multiplier Outer Steering Ring", FieldType::Float}},
        {"ADS Multiplier Friction", {"ADS Multiplier Friction", FieldType::Float}},
        {"ADS Multiplier Steering Degrees Per Sec", {"ADS Multiplier Steering Degrees Per Sec", FieldType::Float}}
    }}},
    {"SOUN", {"'Sound Marker'", {
        {"Radius", {"Radius", FieldType::Float}}
    }}},
    {"SPCH", {"'Speech Challenge'", {

    }}},
    {"SPED", {"Movement Data", {
        {"Unused", {"Unused", FieldType::Float}},
        {"Walk", {"Walk", FieldType::Float}},
        {"Jog", {"Jog", FieldType::Float}},
        {"Run", {"Run", FieldType::Float}},
        {"Sprint", {"Sprint", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}}
    }}},
    {"SPEL", {"'Spell'", {

    }}},
    {"SPGD", {"'Shader Particle Geometry'", {
        {"Gravity Velocity", {"Gravity Velocity", FieldType::Float}},
        {"Rotation Velocity", {"Rotation Velocity", FieldType::Float}},
        {"Particle Size X", {"Particle Size X", FieldType::Float}},
        {"Particle Size Y", {"Particle Size Y", FieldType::Float}},
        {"Center Offset Min", {"Center Offset Min", FieldType::Float}},
        {"Center Offset Max", {"Center Offset Max", FieldType::Float}},
        {"Initial Rotation", {"Initial Rotation", FieldType::Float}},
        {"# of Subtextures X", {"# of Subtextures X", FieldType::Int32}},
        {"# of Subtextures Y", {"# of Subtextures Y", FieldType::Int32}},
        {"Box Size", {"Box Size", FieldType::Int32}},
        {"Particle Density", {"Particle Density", FieldType::Float}},
        {"MNAM", {"MNAM", FieldType::String}}
    }}},
    {"SPIT", {"Data", {
        {"Base Cost", {"Base Cost", FieldType::Int32}}
    }}},
    {"STAG", {"'Animation Sound Tag Set'", {
        {"STAE", {"STAE", FieldType::String}}
    }}},
    {"STAT", {"'Static'", {
        {"Max Angle (30-120", {"Max Angle (30-120", FieldType::Float}},
        {"Leaf Amplitude", {"Leaf Amplitude", FieldType::Float}},
        {"Leaf Frequency", {"Leaf Frequency", FieldType::Float}}
    }}},
    {"STBH", {"'Snap Template Behavior'", {

    }}},
    {"STDT", {"'Star'", {
        {"ANAM", {"ANAM", FieldType::String}}
    }}},
    {"STMP", {"'Snap Template'", {
        {"Instance ID", {"Instance ID", FieldType::Int32}},
        {"Display Case Slot", {"Display Case Slot", FieldType::Int32}},
        {"CNAM", {"CNAM", FieldType::String}}
    }}},
    {"STND", {"'Snap Template Node'", {
        {"FLTV", {"FLTV", FieldType::Float}}
    }}},
    {"SUNP", {"'Sun Preset'", {

    }}},
    {"TACT", {"'Talking Activator'", {
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}}
    }}},
    {"TERM", {"'Terminal'", {
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}},
        {"XMRK", {"XMRK", FieldType::String}},
        {"STRV", {"STRV", FieldType::String}}
    }}},
    {"TES4", {"'Main File Header'", {
        {"FormType", {"FormType", FieldType::Int32}},
        {"BNAM", {"BNAM", FieldType::String}}
    }}},
    {"TIQS", {"Set Parent Quest Stage", {
        {"On Begin", {"On Begin", FieldType::Int32}},
        {"On End", {"On End", FieldType::Int32}}
    }}},
    {"TLOD", {"'TLOD'", {

    }}},
    {"TMLM", {"'Terminal Menu'", {

    }}},
    {"TNAM", {"Transient Type", {
        {"FormType", {"FormType", FieldType::Int32}}
    }}},
    {"TODD", {"'Time Of Day Data'", {

    }}},
    {"TOFT", {"'TOFT'", {

    }}},
    {"TRAV", {"'Traversal'", {
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Unknown", {"Unknown", FieldType::Int32}}
    }}},
    {"TRNS", {"'Transform'", {
        {"Scale", {"Scale", FieldType::Float}},
        {"Zoom Min", {"Zoom Min", FieldType::Float}},
        {"Zoom Max", {"Zoom Max", FieldType::Float}}
    }}},
    {"TXST", {"'Texture Set'", {
        {"TX00", {"TX00", FieldType::String}},
        {"TX01", {"TX01", FieldType::String}},
        {"TX03", {"TX03", FieldType::String}},
        {"TX04", {"TX04", FieldType::String}},
        {"TX05", {"TX05", FieldType::String}},
        {"TX02", {"TX02", FieldType::String}},
        {"TX06", {"TX06", FieldType::String}},
        {"TX07", {"TX07", FieldType::String}},
        {"TX08", {"TX08", FieldType::String}},
        {"TX09", {"TX09", FieldType::String}},
        {"TX17", {"TX17", FieldType::String}},
        {"TX19", {"TX19", FieldType::String}},
        {"MNAM", {"MNAM", FieldType::String}}
    }}},
    {"VCTT", {"Weapon Data", {
        {"Offset X", {"Offset X", FieldType::Float}},
        {"Offset Y", {"Offset Y", FieldType::Float}},
        {"Offset Z", {"Offset Z", FieldType::Float}},
        {"Pitch", {"Pitch", FieldType::Float}},
        {"Yaw", {"Yaw", FieldType::Float}},
        {"Roll", {"Roll", FieldType::Float}},
        {"Scale", {"Scale", FieldType::Float}}
    }}},
    {"VENV", {"Vendor Values", {
        {"Start Hour", {"Start Hour", FieldType::Int32}},
        {"End Hour", {"End Hour", FieldType::Int32}},
        {"Radius", {"Radius", FieldType::Float}}
    }}},
    {"VMRT", {"Vehicle Material Table", {
        {"Count", {"Count", FieldType::Int32}}
    }}},
    {"VOLI", {"'Volumetric Lighting'", {

    }}},
    {"VTYP", {"'Voice Type'", {

    }}},
    {"WAIM", {"Aim", {
        {"Sighted Transition (Seconds", {"Sighted Transition (Seconds", FieldType::Float}}
    }}},
    {"WATR", {"'Water'", {
        {"ANAM", {"ANAM", FieldType::Int32}},
        {"Depth Amount", {"Depth Amount", FieldType::Float}},
        {"Red", {"Red", FieldType::Float}},
        {"Green", {"Green", FieldType::Float}},
        {"Blue", {"Blue", FieldType::Float}},
        {"Phytoplankton", {"Phytoplankton", FieldType::Float}},
        {"Sediment", {"Sediment", FieldType::Float}},
        {"Yellow Matter", {"Yellow Matter", FieldType::Float}},
        {"Oceanness", {"Oceanness", FieldType::Float}},
        {"Fog Amount", {"Fog Amount", FieldType::Float}},
        {"Near Fog", {"Near Fog", FieldType::Float}},
        {"Far Fog", {"Far Fog", FieldType::Float}},
        {"Normal Magnitude", {"Normal Magnitude", FieldType::Float}},
        {"Shallow Normal Falloff", {"Shallow Normal Falloff", FieldType::Float}},
        {"Deep Normal Falloff", {"Deep Normal Falloff", FieldType::Float}},
        {"Surface Effect Falloff", {"Surface Effect Falloff", FieldType::Float}},
        {"Force", {"Force", FieldType::Float}},
        {"Velocity", {"Velocity", FieldType::Float}},
        {"Falloff", {"Falloff", FieldType::Float}},
        {"Dampener", {"Dampener", FieldType::Float}},
        {"Starting Size", {"Starting Size", FieldType::Float}},
        {"Layer 1 - Wind Direction", {"Layer 1 - Wind Direction", FieldType::Float}},
        {"Layer 2 - Wind Direction", {"Layer 2 - Wind Direction", FieldType::Float}},
        {"Layer 3 - Wind Direction", {"Layer 3 - Wind Direction", FieldType::Float}},
        {"Layer 1 - Wind Speed", {"Layer 1 - Wind Speed", FieldType::Float}},
        {"Layer 2 - Wind Speed", {"Layer 2 - Wind Speed", FieldType::Float}},
        {"Layer 3 - Wind Speed", {"Layer 3 - Wind Speed", FieldType::Float}},
        {"Layer 1 - Amplitude Scale", {"Layer 1 - Amplitude Scale", FieldType::Float}},
        {"Layer 2 - Amplitude Scale", {"Layer 2 - Amplitude Scale", FieldType::Float}},
        {"Layer 3 - Amplitude Scale", {"Layer 3 - Amplitude Scale", FieldType::Float}},
        {"Layer 1 - UV Scale", {"Layer 1 - UV Scale", FieldType::Float}},
        {"Layer 2 - UV Scale", {"Layer 2 - UV Scale", FieldType::Float}},
        {"Layer 3 - UV Scale", {"Layer 3 - UV Scale", FieldType::Float}},
        {"Layer 1 - Noise Falloff", {"Layer 1 - Noise Falloff", FieldType::Float}},
        {"Layer 2 - Noise Falloff", {"Layer 2 - Noise Falloff", FieldType::Float}},
        {"Layer 3 - Noise Falloff", {"Layer 3 - Noise Falloff", FieldType::Float}},
        {"Flowmap Scale", {"Flowmap Scale", FieldType::Float}},
        {"Roughnes", {"Roughnes", FieldType::Float}}
    }}},
    {"WBAR", {"'Weapon Barrel Model'", {
        {"Distance From Wall", {"Distance From Wall", FieldType::Float}},
        {"GunUp to GunDown Transition Duration (s", {"GunUp to GunDown Transition Duration (s", FieldType::Float}},
        {"GunDown to GunUp Transition Duration (s", {"GunDown to GunUp Transition Duration (s", FieldType::Float}}
    }}},
    {"WCHG", {"Charge Data", {
        {"Full Power (Seconds", {"Full Power (Seconds", FieldType::Float}},
        {"Min Power Per Shot", {"Min Power Per Shot", FieldType::Float}},
        {"Crit Charge Bonus", {"Crit Charge Bonus", FieldType::Float}}
    }}},
    {"WDMG", {"Damage", {
        {"Base Damage", {"Base Damage", FieldType::Float}},
        {"Range - Min", {"Range - Min", FieldType::Float}},
        {"Range - Max", {"Range - Max", FieldType::Float}},
        {"Out of Range Damage Mult", {"Out of Range Damage Mult", FieldType::Float}},
        {"Crit Damage Mult", {"Crit Damage Mult", FieldType::Float}}
    }}},
    {"WEAP", {"'Weapon'", {
        {"Sighted Transition (Seconds", {"Sighted Transition (Seconds", FieldType::Float}},
        {"Accuracy Bonus", {"Accuracy Bonus", FieldType::Int32}},
        {"Ammo Capacity", {"Ammo Capacity", FieldType::Int32}},
        {"Projectiles Count", {"Projectiles Count", FieldType::Int32}},
        {"Number of Impact Sounds", {"Number of Impact Sounds", FieldType::Int32}},
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}},
        {"Heading Speed", {"Heading Speed", FieldType::Float}},
        {"Pitch Speed", {"Pitch Speed", FieldType::Float}},
        {"Accuracy", {"Accuracy", FieldType::Float}},
        {"Full Power (Seconds", {"Full Power (Seconds", FieldType::Float}},
        {"Min Power Per Shot", {"Min Power Per Shot", FieldType::Float}},
        {"Crit Charge Bonus", {"Crit Charge Bonus", FieldType::Float}},
        {"Base Damage", {"Base Damage", FieldType::Float}},
        {"Range - Min", {"Range - Min", FieldType::Float}},
        {"Range - Max", {"Range - Max", FieldType::Float}},
        {"Out of Range Damage Mult", {"Out of Range Damage Mult", FieldType::Float}},
        {"Crit Damage Mult", {"Crit Damage Mult", FieldType::Float}},
        {"Scale Control Point", {"Scale Control Point", FieldType::Float}},
        {"Crit Chance Inc Mult", {"Crit Chance Inc Mult", FieldType::Float}},
        {"Burst count", {"Burst count", FieldType::Int32}},
        {"Attack (Seconds", {"Attack (Seconds", FieldType::Float}},
        {"Fire (Seconds", {"Fire (Seconds", FieldType::Float}},
        {"Attack Delay (Seconds", {"Attack Delay (Seconds", FieldType::Float}},
        {"Bolt Charge (Seconds", {"Bolt Charge (Seconds", FieldType::Float}},
        {"Shots Per Second", {"Shots Per Second", FieldType::Float}},
        {"Weapon Attack Animation Duration", {"Weapon Attack Animation Duration", FieldType::Float}},
        {"Trigger Threshold - Primary Trigger", {"Trigger Threshold - Primary Trigger", FieldType::Float}},
        {"Trigger Threshold - Second Stage", {"Trigger Threshold - Second Stage", FieldType::Float}},
        {"Burst Delay (Seconds", {"Burst Delay (Seconds", FieldType::Float}},
        {"Base weight", {"Base weight", FieldType::Float}},
        {"Base value", {"Base value", FieldType::Int32}},
        {"Base Speed", {"Base Speed", FieldType::Float}},
        {"Attack Oxygen Cost", {"Attack Oxygen Cost", FieldType::Float}},
        {"Bash Damage", {"Bash Damage", FieldType::Float}},
        {"Reach", {"Reach", FieldType::Float}},
        {"Recharge time", {"Recharge time", FieldType::Float}},
        {"Recharge delay", {"Recharge delay", FieldType::Float}},
        {"Variable Power Transition Duration", {"Variable Power Transition Duration", FieldType::Float}},
        {"Power Damage Multiplier", {"Power Damage Multiplier", FieldType::Float}},
        {"Reload Seconds", {"Reload Seconds", FieldType::Float}},
        {"Reload Speed", {"Reload Speed", FieldType::Float}},
        {"Value - Min", {"Value - Min", FieldType::Float}},
        {"Value - Max", {"Value - Max", FieldType::Float}},
        {"Input - Min", {"Input - Min", FieldType::Float}},
        {"Input - Max", {"Input - Max", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}},
        {"MOD4", {"MOD4", FieldType::String}},
        {"MO4S", {"MO4S", FieldType::Float}},
        {"Color Remapping Index", {"Color Remapping Index", FieldType::Float}},
        {"Attack Action Point Cost", {"Attack Action Point Cost", FieldType::Float}},
        {"Firing Camera Shake Intensity", {"Firing Camera Shake Intensity", FieldType::Float}},
        {"Firing Camera Shake Duration", {"Firing Camera Shake Duration", FieldType::Float}},
        {"AI Firing Arc", {"AI Firing Arc", FieldType::Float}}
    }}},
    {"WGEN", {"General", {
        {"Base weight", {"Base weight", FieldType::Float}},
        {"Base value", {"Base value", FieldType::Int32}},
        {"Base Speed", {"Base Speed", FieldType::Float}},
        {"Attack Oxygen Cost", {"Attack Oxygen Cost", FieldType::Float}}
    }}},
    {"WKMF", {"'Wwise Keyword Mapping'", {

    }}},
    {"WMEL", {"Melee", {
        {"Bash Damage", {"Bash Damage", FieldType::Float}},
        {"Reach", {"Reach", FieldType::Float}}
    }}},
    {"WOOP", {"'Word of Power'", {

    }}},
    {"WRLD", {"'Worldspace'", {
        {"NAM7", {"NAM7", FieldType::String}},
        {"ICON", {"ICON", FieldType::String}},
        {"NAMA", {"NAMA", FieldType::Float}},
        {"XEMP", {"XEMP", FieldType::String}},
        {"XWEM", {"XWEM", FieldType::String}},
        {"GNAM", {"GNAM", FieldType::Float}}
    }}},
    {"WRLO", {"Reload", {
        {"Reload Seconds", {"Reload Seconds", FieldType::Float}},
        {"Reload Speed", {"Reload Speed", FieldType::Float}}
    }}},
    {"WTHR", {"'Weather'", {
        {"Unknown", {"Unknown", FieldType::Float}},
        {"Wind Speed", {"Wind Speed", FieldType::Int32}},
        {"Trans Delta", {"Trans Delta", FieldType::Int32}},
        {"Sun Glare", {"Sun Glare", FieldType::Int32}},
        {"Sun Damage", {"Sun Damage", FieldType::Int32}},
        {"Precipitation - Begin Fade In", {"Precipitation - Begin Fade In", FieldType::Int32}},
        {"Precipitation - End Fade Out", {"Precipitation - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Begin Fade In", {"Thunder/Lightning - Begin Fade In", FieldType::Int32}},
        {"Thunder/Lightning - End Fade Out", {"Thunder/Lightning - End Fade Out", FieldType::Int32}},
        {"Thunder/Lightning - Frequency", {"Thunder/Lightning - Frequency", FieldType::Int32}},
        {"Visual Effect - Begin", {"Visual Effect - Begin", FieldType::Int32}},
        {"Visual Effect - End", {"Visual Effect - End", FieldType::Int32}},
        {"Wind Direction", {"Wind Direction", FieldType::Int32}},
        {"Wind Direction Range", {"Wind Direction Range", FieldType::Int32}},
        {"Wind Turbulance", {"Wind Turbulance", FieldType::Int32}},
        {"VNAM", {"VNAM", FieldType::Float}},
        {"WNAM", {"WNAM", FieldType::Float}}
    }}},
    {"WTHS", {"'Weather Settings'", {

    }}},
    {"WTRM", {"Ship Weapon", {
        {"Attack Action Point Cost", {"Attack Action Point Cost", FieldType::Float}},
        {"Firing Camera Shake Intensity", {"Firing Camera Shake Intensity", FieldType::Float}},
        {"Firing Camera Shake Duration", {"Firing Camera Shake Duration", FieldType::Float}},
        {"AI Firing Arc", {"AI Firing Arc", FieldType::Float}}
    }}},
    {"WTUR", {"Turret", {
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}}
    }}},
    {"WVAR", {"Variable Range", {
        {"Value - Min", {"Value - Min", FieldType::Float}},
        {"Value - Max", {"Value - Max", FieldType::Float}},
        {"Input - Min", {"Input - Min", FieldType::Float}},
        {"Input - Max", {"Input - Max", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}}
    }}},
    {"WWED", {"'Wwise Event Data'", {

    }}},
    {"XBSD", {"Bendable Spline", {
        {"Slack", {"Slack", FieldType::Float}},
        {"Thickness", {"Thickness", FieldType::Float}}
    }}},
    {"XCLL", {"Lighting", {
        {"Fog Near", {"Fog Near", FieldType::Float}},
        {"Fog Far", {"Fog Far", FieldType::Float}},
        {"Directional Rotation XY", {"Directional Rotation XY", FieldType::Int32}},
        {"Directional Rotation Z", {"Directional Rotation Z", FieldType::Int32}},
        {"Gravity Scale", {"Gravity Scale", FieldType::Float}},
        {"Fog Clip Distance", {"Fog Clip Distance", FieldType::Float}},
        {"Fog Power", {"Fog Power", FieldType::Float}},
        {"Fog Max", {"Fog Max", FieldType::Float}},
        {"Light Fade Begin", {"Light Fade Begin", FieldType::Float}},
        {"Light Fade End", {"Light Fade End", FieldType::Float}},
        {"Near Height Mid", {"Near Height Mid", FieldType::Float}},
        {"Near Height Range", {"Near Height Range", FieldType::Float}},
        {"High Density Scale", {"High Density Scale", FieldType::Float}},
        {"Fog Near Scale", {"Fog Near Scale", FieldType::Float}},
        {"Fog Far Scale", {"Fog Far Scale", FieldType::Float}},
        {"Fog High Near Scale", {"Fog High Near Scale", FieldType::Float}},
        {"Fog High Far Scale", {"Fog High Far Scale", FieldType::Float}},
        {"Far Height Mid", {"Far Height Mid", FieldType::Float}},
        {"Far Height Range", {"Far Height Range", FieldType::Float}}
    }}},
    {"XCNT", {"Footstep Counts", {
        {"Walking Count", {"Walking Count", FieldType::Int32}},
        {"Running Count", {"Running Count", FieldType::Int32}},
        {"Sprinting Count", {"Sprinting Count", FieldType::Int32}},
        {"Sneaking Count", {"Sneaking Count", FieldType::Int32}},
        {"Swimming Count", {"Swimming Count", FieldType::Int32}}
    }}},
    {"XCOL", {"Collision", {
        {"Collision Layer", {"Collision Layer", FieldType::Int32}}
    }}},
    {"XDTF", {"Format", {
        {"Size", {"Size", FieldType::Int32}}
    }}},
    {"XEED", {"External Emittance", {
        {"External Emittance Luminance Scale", {"External Emittance Luminance Scale", FieldType::Float}}
    }}},
    {"XLBD", {"Barndoors", {
        {"Bottom", {"Bottom", FieldType::Float}},
        {"Right 1.0+/-", {"Right 1.0+/-", FieldType::Float}},
        {"Left", {"Left", FieldType::Float}},
        {"Top 1.0+/-", {"Top 1.0+/-", FieldType::Float}},
        {"Falloff Intensity 100.0+/-", {"Falloff Intensity 100.0+/-", FieldType::Float}}
    }}},
    {"XLFD", {"Light Flicker", {
        {"Period", {"Period", FieldType::Float}},
        {"Intensity Amplitude", {"Intensity Amplitude", FieldType::Float}},
        {"Movement Amplitude", {"Movement Amplitude", FieldType::Float}}
    }}},
    {"XLGD", {"Gobo Animated Properties", {
        {"Static Rotation", {"Static Rotation", FieldType::Float}},
        {"Animated Rotation Speed", {"Animated Rotation Speed", FieldType::Float}},
        {"Animated Wave Rotation Speed", {"Animated Wave Rotation Speed", FieldType::Float}},
        {"Animated Wave Rotation Amount", {"Animated Wave Rotation Amount", FieldType::Float}},
        {"Static Scale U 1.0+/-", {"Static Scale U 1.0+/-", FieldType::Float}},
        {"Static Scale V 1.0+/-", {"Static Scale V 1.0+/-", FieldType::Float}},
        {"Wave Scaling U Speed", {"Wave Scaling U Speed", FieldType::Float}},
        {"Wave Scaling V Speed", {"Wave Scaling V Speed", FieldType::Float}},
        {"Wave Scaling U Amount", {"Wave Scaling U Amount", FieldType::Float}},
        {"Wave Scaling V Amount", {"Wave Scaling V Amount", FieldType::Float}},
        {"Static Offset U", {"Static Offset U", FieldType::Float}},
        {"Static Offset V", {"Static Offset V", FieldType::Float}},
        {"Rotation Pivot U 0.5+/-", {"Rotation Pivot U 0.5+/-", FieldType::Float}},
        {"Rotation Pivot V 0.5+/-", {"Rotation Pivot V 0.5+/-", FieldType::Float}},
        {"Scroll Speed U", {"Scroll Speed U", FieldType::Float}},
        {"Scroll Speed V", {"Scroll Speed V", FieldType::Float}},
        {"Wave Scroll Speed U", {"Wave Scroll Speed U", FieldType::Float}},
        {"Wave Scroll Speed V", {"Wave Scroll Speed V", FieldType::Float}},
        {"Wave Scroll Amount U", {"Wave Scroll Amount U", FieldType::Float}},
        {"Wave Scroll Amount V", {"Wave Scroll Amount V", FieldType::Float}},
        {"Random Time Offset Range", {"Random Time Offset Range", FieldType::Float}}
    }}},
    {"XLIG", {"Light Data", {
        {"FOV 90+/-", {"FOV 90+/-", FieldType::Float}},
        {"Luminous Scale", {"Luminous Scale", FieldType::Float}},
        {"End Distance Cap", {"End Distance Cap", FieldType::Float}},
        {"Near Clip/Cut On", {"Near Clip/Cut On", FieldType::Float}},
        {"Inner FOV", {"Inner FOV", FieldType::Float}},
        {"Shadow Offset", {"Shadow Offset", FieldType::Float}},
        {"XRDS", {"XRDS", FieldType::Float}}
    }}},
    {"XMPM", {"Unknown", {
        {"Extension", {"Extension", FieldType::String}}
    }}},
    {"XNAM", {"Property", {
        {"Value", {"Value", FieldType::Float}}
    }}},
    {"XPDD", {"Projected Decal Data", {
        {"Width Scale", {"Width Scale", FieldType::Float}},
        {"Height Scale", {"Height Scale", FieldType::Float}},
        {"Unknown", {"Unknown", FieldType::Int32}}
    }}},
    {"ZNAM", {"Data", {
        {"Distance From Wall", {"Distance From Wall", FieldType::Float}},
        {"GunUp to GunDown Transition Duration (s", {"GunUp to GunDown Transition Duration (s", FieldType::Float}},
        {"GunDown to GunUp Transition Duration (s", {"GunDown to GunUp Transition Duration (s", FieldType::Float}}
    }}},
    {"ZOOM", {"'Zoom'", {
        {"FOV Mult", {"FOV Mult", FieldType::Float}},
        {"FOV Offset", {"FOV Offset", FieldType::Float}},
        {"Offset Duration", {"Offset Duration", FieldType::Float}}
    }}},
};

// Tags that are universal to almost all records
inline std::map<std::string, TagInfo> g_CommonTags = {
    {"EDID", {"Editor ID", FieldType::String}},
    {"FULL", {"Full Name", FieldType::String}},
};

#endif
