#ifndef PGRE_H
#define PGRE_H

struct PGRE {
    zstring edid;
    formid name;
    uint8_t XIS2[0];
    float xscl;
    uint8_t XESP[8];
    formid xown;
    uint8_t DATA[24];
};


#endif