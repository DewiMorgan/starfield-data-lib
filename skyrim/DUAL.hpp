#ifndef DUAL_HPP
#define DUAL_HPP

#include "base_types.hpp"
#include "OBND.hpp"
#include "core.hpp"

struct DUAL : public Record {
    zstring editorId;
    OBND objectBounds;
    uint8 dataRaw[24]; // 5 FormIDs (20 bytes) + uint32 flags

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
