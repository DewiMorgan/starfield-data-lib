#ifndef MOVT_H
#define MOVT_H

#include "base_types.hpp"
#include "core.hpp"
#include <vector>

struct MOVT : public Record {
    ZString editorId;
    ZString name;
    std::vector<uint8_t> defaultData;  // SPED: 40 or 44 bytes of movement data
    float animThresholds[3];              // INAM: Direction, Speed, Rotation scale

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
    bool validate() override;
};

#endif