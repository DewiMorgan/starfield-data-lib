#ifndef PHZD_H
#define PHZD_H

struct PHZD {
    VMAD scripting;
    FormID base_hazard;
    XIS2 xis2;
    float scale;
    XESP enable_parent;
    DATA coords;
    FormID location;
};


#endif