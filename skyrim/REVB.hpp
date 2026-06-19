#ifndef REVB_H
#define REVB_H

#include "core.hpp"

struct REVB : public Record {
    ZString editorId;
    uint8 data[14];

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
};

#endif