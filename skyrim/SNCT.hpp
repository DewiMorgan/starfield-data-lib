#ifndef SNCT_H
#define SNCT_H

#include "core.hpp"

struct SNCT : public Record {
    ZString editorId;
    std::string fullName;
    uint32 flags;
    FormID parentName;
    uint16 staticVolumeMult;
    uint16 defaultMenuValue;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
};

#endif