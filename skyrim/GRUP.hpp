#ifndef GRUP_H
#define GRUP_H

struct GRUP {
    char type[4];
    uint32 size;
    uint8 label[4];
    int32 groupType;
    uint16 timestamp;
    uint16 versionControl;
    uint32 unknown;
    std::vector<uint8> records;
};


#endif