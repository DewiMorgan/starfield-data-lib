#ifndef QUST_H
#define QUST_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include "SCHR.hpp"
#include <vector>
#include <string>

struct QuestLogEntry {
    uint8 flags;
    std::vector<CTDA> conditions;
    lstring journalEntry;
    FormID nextQuest;
    std::vector<SCHR> oldScript;
};

struct QuestStage {
    int16 index;
    uint8 flags;
    int8 unknown;
    std::vector<QuestLogEntry> logEntries;
};

struct QuestTarget {
    int32 targetAlias;
    int32 flags;
    std::vector<CTDA> conditions;
};

struct QuestObjective {
    int16 index;
    int32 flags;
    lstring nodeName;
    std::vector<QuestTarget> targets;
};

struct Alias {
    uint32 aliasId;
    ZString aliasName;
    uint32 flags;
    FormID forcedInto;
    std::vector<uint8> fillData;
    std::vector<CTDA> matchConditions;
    uint32 kwdaCount;
    std::vector<FormID> kwda;
    uint32 cntoCount;
    std::vector<uint8> cntoData;
    FormID spectatorOverride;
    FormID observeCorpse;
    FormID guardWarnOverride;
    FormID combatOverride;
    FormID displayName;
};

struct QUST {
    ZString edid;
    VMAD vmad;
    lstring fullName;
    uint8 data_flags1;
    uint8 data_flags2;
    uint8 data_priority;
    uint8 data_unknown;
    int32 data_unknown2;
    uint32 data_questType;
    char event_name[4];
    std::vector<FormID> qtgl;
    ZString filter;
    std::vector<CTDA> dialogueConditions;
    uint8 next_marker;
    std::vector<CTDA> eventConditions;
    std::vector<QuestStage> stages;
    std::vector<QuestObjective> objectives;
    int32 nextAliasId;
    std::vector<Alias> aliases;
};

#endif
