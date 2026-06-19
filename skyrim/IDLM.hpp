#ifndef IDLM_HPP
#define IDLM_HPP

#include "base_types.hpp"
#include "core.hpp"

struct IDLM : public Record {
    zstring editorId;
    OBND objectBounds;
    uint8 flags;
    uint8 idleCount;
    float idleTimer;
    std::vector<FormID> idleAnimations;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
