#ifndef IDLE_HPP
#define IDLE_HPP

#include "base_types.hpp"
#include "core.hpp"

// IDLE Data: 6 bytes (min/max loop secs, flags, unknown, replayDelay)
struct IDLE : public Record {
    zstring editorId;
    std::vector<uint8> scriptDataRaw; // raw CTDA entries
    zstring havokFile;
    zstring animEvent;
    FormID animations[2];
    uint8 dataRaw[6]; // 6-byte DATA struct

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
