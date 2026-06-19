#ifndef LCRT_HPP
#define LCRT_HPP

#include "core.hpp"
#include "base_types.hpp"

struct LCRT : public Record {
    ZString editorId;   // EDID: editor ID
    rgb colorCode;      // CNAM: RGB color code (3 bytes)

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif