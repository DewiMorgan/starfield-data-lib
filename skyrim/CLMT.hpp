#ifndef CLMT_HPP
#define CLMT_HPP

#include "base_types.hpp"
#include "MODL.hpp"
#include "core.hpp"

struct CLMT : public Record {
    zstring editorId;
    std::vector<uint8> wlstData; // 12 bytes per weather entry (formid + uint32 + formid)
    zstring sunTexture;
    zstring glareTexture;
    MODL nightSkyModel;
    uint8 sunAndMoon[6];

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
