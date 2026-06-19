#ifndef VTYP_H
#define VTYP_H

#include "core.hpp"

struct VTYP : public Record {
    ZString editorId;
    uint8 type;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
};

#endif