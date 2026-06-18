#ifndef ECZN_HPP
#define ECZN_HPP

#include "core.hpp"
#include "base_types.hpp"

class ECZN : public Record {
public:
    zstring editorId;
    uint8 data[12];

    ECZN() : Record("ECZN") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
