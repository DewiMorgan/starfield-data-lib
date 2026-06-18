#ifndef EYES_HPP
#define EYES_HPP

#include "core.hpp"
#include "base_types.hpp"

class EYES : public Record {
public:
    zstring editorId;
    lstring description;
    zstring path;
    uint8 type;

    EYES() : Record("EYES") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
