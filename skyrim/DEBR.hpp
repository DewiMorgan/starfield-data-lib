#ifndef DEBR_HPP
#define DEBR_HPP

#include "base_types.hpp"
#include "core.hpp"

struct DEBRData {
    uint8 percentage;
    zstring modelPath;
    uint8 flags;
};

struct DEBR : public Record {
    zstring editorId;
    std::vector<DEBRData> directionalData;
    std::vector<uint8> modelDataRaw; // raw MODT bytes

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
