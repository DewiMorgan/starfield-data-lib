#ifndef MATT_H
#define MATT_H

#include "base_types.hpp"
#include "core.hpp"
#include <array>

struct MATT : public Record {
    ZString editorId;
    ZString materialName;
    FormID havokImpactData;  // HNAM
    FormID parentMaterial;   // PNAM
    std::array<float, 3> color;        // CNAM: float[3]
    float buoyancy;                    // BNAM
    uint32_t flags;                    // FNAM

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
    bool validate() override;
};

#endif
