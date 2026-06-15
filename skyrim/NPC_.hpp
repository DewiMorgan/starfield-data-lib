#ifndef NPC__H
#define NPC__H

#include "base_types.hpp"
#include <vector>
#include <string>
#include <array>

struct NPCFaction {
    FormID faction;
    int8 rank;
};

struct NPCAttackData {
    float damageMult;
    float attackChance;
    FormID attackSpell;
    uint32 flags;
    float attackAngle;
    float strikeAngle;
    float stagger;
    FormID attackType;
    float knockdown;
    float recoveryTime;
    float fatigueMult;
};

struct NPCAttackEvent {
    NPCAttackData data;
    ZString event;
};

struct NPCPerk {
    FormID perk;
    uint8 rank;
};

struct NPCContainerObject {
    FormID item;
    uint32 count;
};

struct NPC_AIData {
    uint8 aggression;
    uint8 confidence;
    uint8 energy;
    uint8 morality;
    uint8 mood;
    uint8 assistance;
    uint8 flags;
    uint8 unknown;
    uint32 warn;
    uint32 warnAttack;
    uint32 attack;
};

struct NPC_SkillStatData {
    std::array<uint8, 18> baseSkills;
    std::array<uint8, 18> modSkills;
    uint16 calcHealth;
    uint16 calcMagicka;
    uint16 calcStamina;
    uint16 unused;
    float farAwayModelDist;
    uint8 gearedUpWeapons;
    uint8 junk[3];
};

struct NPC_SkinTone {
    float r, g, b;
};

struct NPC_FaceMorphs {
    std::array<float, 19> morphs;
    uint32 unknown;
};

struct NPC_FacePart {
    int32 nose;
    int32 unknown;
    int32 eyes;
    int32 mouth;
};

struct NPCTintLayer {
    uint16 tintIndex;
    uint8 tintColor[4];
    int32 tintValue;
    int16 tintSash;
};

struct NPC_ {
    ZString edid;
    VMAD vmad;
    OBND obnd;
    
    struct BaseStats {
        uint32 flags;
        int16 magickaOffset;
        int16 staminaOffset;
        uint16 level;
        uint16 calcMinLevel;
        uint16 calcMaxLevel;
        uint16 speedMult;
        uint16 dispositionBase;
        uint16 templateFlags;
        int16 healthOffset;
        uint16 bleedoutOverride;
    } baseStats;

    std::vector<NPCFaction> factions;
    FormID deathItem;
    FormID voiceType;
    FormID templateId;
    FormID race;
    DEST dest;
    
    std::vector<FormID> spells;
    FormID wornArmor;
    FormID awayModel;
    FormID attackRace;
    
    std::vector<NPCAttackEvent> attacks;

    FormID spectatorOverride;
    FormID observeCorpse;
    FormID guardWarnOverride;
    FormID combatOverride;
    
    std::vector<NPCPerk> perks;
    std::vector<NPCContainerObject> containerObjects;
    COED owner;
    
    NPC_AIData aiData;
    std::vector<FormID> aiPackages;
    
    std::vector<FormID> keywords;
    FormID classId;
    lstring fullName;
    lstring shortAlias;
    
    NPC_SkillStatData skillStatData;
    std::vector<FormID> headParts;
    FormID hairColor;
    FormID combatStyle;
    FormID giftFilter;
    
    uint16 nam5;
    float height;
    float weight;
    uint32 soundLevel;
    
    struct SoundEntry {
        uint32 type;
        FormID sound;
        uint8 chance;
    };
    std::vector<SoundEntry> sounds;
    FormID audioTemplate;
    
    FormID defaultOutfit;
    FormID sleepOutfit;
    FormID defaultPackList;
    FormID crimeFaction;
    FormID faceTexture;
    
    NPC_SkinTone skinTone;
    NPC_FaceMorphs faceMorphs;
    std::vector<NPC_FacePart> faceParts;
    std::vector<NPCTintLayer> tintLayers;
};

#endif
