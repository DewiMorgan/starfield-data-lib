#ifndef CLFM_HPP
#define CLFM_HPP

#include "core.hpp"
#include "base_types.hpp"

class CLFM : public Record {
public:
    zstring editorId;
    lstring full;
    rgb cnam;
    uint32 fnam;

    CLFM() : Record("CLFM") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
