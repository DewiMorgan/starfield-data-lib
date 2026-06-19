#ifndef ASPC_HPP
#define ASPC_HPP

#include "base_types.hpp"
#include "core.hpp"
#include "OBND.hpp"

struct ASPC : public Record {
    zstring editorId;
    OBND objectBounds;
    FormID ambient;
    FormID regionData;
    FormID reverb;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
