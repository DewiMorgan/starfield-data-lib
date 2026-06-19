#ifndef MUSC_H
#define MUSC_H

#include "base_types.hpp"
#include "core.hpp"
#include <vector>

struct MUSC : public Record {
    ZString editorId;
    uint32_t flags;              // FNAM: bitfield flags
    struct {                    // PNAM: 4-byte struct
        uint16_t priority;
        uint16_t duckingDb;     // scaled by 100
    } data;
    float fadeDuration;          // WNAM
    std::vector<FormID> musicTracks;  // TNAM: repeating formid[]

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
    bool validate() override;
};

#endif