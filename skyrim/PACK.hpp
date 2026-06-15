#ifndef PACK_H
#define PACK_H

#include "base_types.hpp"
#include "CTDA.hpp"
#include <vector>
#include <string>

struct PACKSchedule {
    int8 month;
    int8 dayOfWeek;
    int8 date;
    int8 hour;
    int8 minute;
    uint8 padding[3];
    uint32 duration;
};

struct PACKActivity {
    zstring activityType;
    std::vector<uint8> data;
};

struct PACKBranch {
    zstring branchType;
    uint32 citc;
    std::vector<CTDA> conditions;
    uint8 prcb[8];
    zstring pnam;
    uint32 fnam;
    std::vector<uint8> pkc2;
    uint8 pfo2[16];
    uint8 pfor[12];
};

struct PACKActivityName {
    uint8 id;
    zstring name;
    uint32 pnam;
};

struct PACK {
    ZString edid;
    VMAD vmad;
    std::vector<CTDA> conditions;
    std::vector<zstring> cis1;
    std::vector<zstring> cis2;
    uint8 idleCount;
    std::vector<FormID> idles;
    uint8 idleFlags;
    float idleTime;
    FormID ownerQuest;
    std::vector<uint8> pkcu;
    std::vector<uint8> pkdt;
    std::vector<PACKActivity> activities;
    std::vector<zstring> activityNames;
    int8 xnam;
    std::vector<PACKBranch> branches;
    std::vector<PACKActivityName> activityData;
    uint8 poba;
    uint8 poea;
    uint8 poca;
};

#endif
