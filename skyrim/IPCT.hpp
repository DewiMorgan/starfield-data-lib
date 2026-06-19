#ifndef IPCT_HPP
#define IPCT_HPP

#include "core.hpp"
#include "base_types.hpp"
#include "MODT.hpp"

class IPCT : public Record {
public:
    zstring editorId;
    std::string model;
    MODT modelTextures;
    uint8 data[24];
    uint8 decalData[56]; // DODT struct: 7 floats + float + uint8 + uint8[3] + rgb = 28+8+1+3+4 = 44? Let me check...
    FormID textureSet;
    FormID secondaryTextureSet;
    FormID impactSound1;
    FormID impactSound2;
    FormID effectHazard;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif