#ifndef TES_H
#define TES_H

struct Unknown0 {
    FormID formID;
    uint16 unknown;
};

struct TES {
    uint32 count1;
    std::vector<Unknown0> unknown0;
    uint32 count2;
    std::vector<FormID> unknown1;
    uint32 count3;
    std::vector<FormID> unknown2;
};


#endif