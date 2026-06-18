#ifndef FSTP_HPP
#define FSTP_HPP

#include "core.hpp"
#include "base_types.hpp"

class FSTP : public Record {
public:
    zstring editorId;
    formid impactData;
    zstring actionName;

    FSTP() : Record("FSTP") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
