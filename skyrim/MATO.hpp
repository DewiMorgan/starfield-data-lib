#ifndef MATO_H
#define MATO_H

#include "base_types.hpp"
#include "core.hpp"
#include <vector>

struct MATO : public Record {
    ZString editorId;
    ZString modelPath;
    std::vector<uint8_t> propertyData;  // DNAM: variable-length
    struct MaterialData {              // DATA: ~48 bytes of floats
        float falloffScale;
        float falloffBias;
        float noiseUVScale;
        float materialUVScale;
        float dirProjVector[3];
        float normalDampener;
        float singlePassColor[3];
        uint32_t singlePassFlag;
    } data;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
    bool validate() override;
};

#endif
