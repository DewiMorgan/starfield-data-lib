#ifndef SOPM_H
#define SOPM_H

struct SOPM {
    ZString editorId;
    NAM1 data;
    uint32 unused_fnam;
    uint32 type;
    uint32 unused_cnam;
    SNAM unused_snam;
    uint8 output_values[8][3];
    ANAM attenuation_values;
};


#endif