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
    {"AIDT", {"AI Data", {
        {"Energy Level", {"Energy Level", FieldType::Int32}}
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
    {"AOR2", {"Data", {
        {"Radius", {"Radius", FieldType::Float}},
        {"Min Delay", {"Min Delay", FieldType::Float}},
        {"Max Delay", {"Max Delay", FieldType::Float}}
    }}},
    {"ATKD", {"Attack Data", {
        {"Damage Mult", {"Damage Mult", FieldType::Float}},
        {"Attack Chance", {"Attack Chance", FieldType::Float}}
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
    {"BODV", {"Configuration", {
        {"Unknown", {"Unknown", FieldType::Int32}}
    }}},
    {"BPD2", {"Data", {
        {"Damage Mult", {"Damage Mult", FieldType::Float}}
    }}},
    {"BSMS", {"Range", {
        {"Min Y", {"Min Y", FieldType::Float}},
        {"Min Z", {"Min Z", FieldType::Float}},
        {"Max Y", {"Max Y", FieldType::Float}},
        {"Max Z", {"Max Z", FieldType::Float}}
    }}},
    {"CNTO", {"[0]", {
        {"Count", {"Count", FieldType::Int32}}
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
    {"DEST", {"Header", {
        {"Health", {"Health", FieldType::Int32}},
        {"Stage Count", {"Stage Count", FieldType::Int32}}
    }}},
    {"DEVT", {"Sound Detection", {
        {"Radius", {"Radius", FieldType::Float}}
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
    {"DODT", {"Decal Data", {
        {"Min Width", {"Min Width", FieldType::Float}},
        {"Max Width", {"Max Width", FieldType::Float}},
        {"Min Height", {"Min Height", FieldType::Float}},
        {"Max Height", {"Max Height", FieldType::Float}},
        {"Depth", {"Depth", FieldType::Float}},
        {"Alpha", {"Alpha", FieldType::Float}}
    }}},
    {"DSTD", {"Data", {
        {"Health %", {"Health %", FieldType::Int32}},
        {"Index", {"Index", FieldType::Int32}},
        {"Model Damage Stage", {"Model Damage Stage", FieldType::Int32}}
    }}},
    {"ENAM", {"Height", {
        {"Min", {"Min", FieldType::Float}},
        {"Max", {"Max", FieldType::Float}}
    }}},
    {"ENIT", {"Effect Data", {
        {"Value", {"Value", FieldType::Int32}}
    }}},
    {"EORI", {"Override - Surface Block Rotations", {
        {"Column", {"Column", FieldType::Int32}}
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
    {"FNAM", {"Data", {
        {"X offset", {"X offset", FieldType::Float}},
        {"Y offset", {"Y offset", FieldType::Float}},
        {"Texture Width", {"Texture Width", FieldType::Int32}},
        {"Texture Height", {"Texture Height", FieldType::Int32}},
        {"Content Width", {"Content Width", FieldType::Int32}},
        {"Content Height", {"Content Height", FieldType::Int32}}
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
    {"KNAM", {"Biome Noise", {
        {"Noise Type", {"Noise Type", FieldType::Int32}},
        {"Terrain Height Seed", {"Terrain Height Seed", FieldType::Int32}},
        {"Terrain Max Height (m", {"Terrain Max Height (m", FieldType::Float}}
    }}},
    {"LFSD", {"Lens Flare Data", {
        {"Width", {"Width", FieldType::Float}},
        {"Height", {"Height", FieldType::Float}},
        {"Position", {"Position", FieldType::Float}},
        {"Angular Fade", {"Angular Fade", FieldType::Float}},
        {"Opacity", {"Opacity", FieldType::Float}}
    }}},
    {"MOBC", {"Base Vertex Color", {
        {"Base Vertex Color", {"Base Vertex Color", FieldType::Int32}}
    }}},
    {"MRSV", {"Body Morph Region Values", {
        {"Head", {"Head", FieldType::Float}},
        {"Upper Torso", {"Upper Torso", FieldType::Float}},
        {"Arms", {"Arms", FieldType::Float}},
        {"Lower Torso", {"Lower Torso", FieldType::Float}},
        {"Legs", {"Legs", FieldType::Float}}
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
    {"NVNM", {"Navmesh Geometry", {
        {"Version", {"Version", FieldType::Int32}}
    }}},
    {"OBTS", {"Object Mod Template Item", {
        {"Level Min", {"Level Min", FieldType::Int32}},
        {"Level Max", {"Level Max", FieldType::Int32}},
        {"Parent Combination Index", {"Parent Combination Index", FieldType::Int32}}
    }}},
    {"ONAM", {"Rotation", {
        {"Min", {"Min", FieldType::Int32}},
        {"Max", {"Max", FieldType::Int32}}
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
    {"PNAM", {"Data", {
        {"Priority", {"Priority", FieldType::Int32}},
        {"Ducking (dB", {"Ducking (dB", FieldType::Int32}}
    }}},
    {"PRCB", {"Root", {
        {"Branch Count", {"Branch Count", FieldType::Int32}}
    }}},
    {"PSDT", {"Schedule", {
        {"Month", {"Month", FieldType::Int32}}
    }}},
    {"QRRD", {"Item", {
        {"Count", {"Count", FieldType::Int32}}
    }}},
    {"RADR", {"Radio Receiver", {
        {"Frequency", {"Frequency", FieldType::Float}},
        {"Volume", {"Volume", FieldType::Float}}
    }}},
    {"SCQS", {"Set Parent Quest Stage", {
        {"On Start", {"On Start", FieldType::Int32}},
        {"On Completion", {"On Completion", FieldType::Int32}}
    }}},
    {"SHWB", {"Ship Weapon Binding", {
        {"Weapon Slot 1", {"Weapon Slot 1", FieldType::Int32}},
        {"Weapon Slot 2", {"Weapon Slot 2", FieldType::Int32}},
        {"Weapon Slot 3", {"Weapon Slot 3", FieldType::Int32}}
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
    {"SPED", {"Movement Data", {
        {"Unused", {"Unused", FieldType::Float}},
        {"Walk", {"Walk", FieldType::Float}},
        {"Jog", {"Jog", FieldType::Float}},
        {"Run", {"Run", FieldType::Float}},
        {"Sprint", {"Sprint", FieldType::Float}},
        {"Acceleration", {"Acceleration", FieldType::Float}},
        {"Deceleration", {"Deceleration", FieldType::Float}}
    }}},
    {"SPIT", {"Data", {
        {"Base Cost", {"Base Cost", FieldType::Int32}}
    }}},
    {"TIQS", {"Set Parent Quest Stage", {
        {"On Begin", {"On Begin", FieldType::Int32}},
        {"On End", {"On End", FieldType::Int32}}
    }}},
    {"TNAM", {"Transient Type", {
        {"FormType", {"FormType", FieldType::Int32}}
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
    {"WAIM", {"Aim", {
        {"Sighted Transition (Seconds", {"Sighted Transition (Seconds", FieldType::Float}}
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
    {"WGEN", {"General", {
        {"Base weight", {"Base weight", FieldType::Float}},
        {"Base value", {"Base value", FieldType::Int32}},
        {"Base Speed", {"Base Speed", FieldType::Float}},
        {"Attack Oxygen Cost", {"Attack Oxygen Cost", FieldType::Float}}
    }}},
    {"WMEL", {"Melee", {
        {"Bash Damage", {"Bash Damage", FieldType::Float}},
        {"Reach", {"Reach", FieldType::Float}}
    }}},
    {"WRLO", {"Reload", {
        {"Reload Seconds", {"Reload Seconds", FieldType::Float}},
        {"Reload Speed", {"Reload Speed", FieldType::Float}}
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
};

// Tags that are universal to almost all records
inline std::map<std::string, TagInfo> g_CommonTags = {
    {"EDID", {"Editor ID", FieldType::String}},
    {"FULL", {"Full Name", FieldType::String}},
};

#endif
