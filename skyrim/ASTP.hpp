#ifndef ASTP_HPP
#define ASTP_HPP

#include "core.hpp"
#include "base_types.hpp"

class ASTP : public Record {
public:
    zstring editorId;
    zstring maleParentLabel;
    zstring femaleParentLabel;
    zstring maleChildLabel;
    zstring femaleChildLabel;
    uint32 flags;

    ASTP() : Record("ASTP") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
