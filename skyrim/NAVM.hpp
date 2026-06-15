#ifndef NAVM_H
#define NAVM_H

struct NAVM {
    NVNM navmeshGeometry;
    std::vector<uint8> onam;
    std::vector<uint8> pnam;
    std::vector<uint8> nnam;
};


#endif