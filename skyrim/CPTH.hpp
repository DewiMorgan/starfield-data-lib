#ifndef CPTH_HPP
#define CPTH_HPP

#include "base_types.hpp"
#include "core.hpp"

struct CPTH : public Record {
    zstring editorId;
    std::vector<uint8> ctdaData; // raw CTDA entries
    zstring ctdaVariable;
    FormID cameraPaths[2];
    uint8 flags;
    std::vector<FormID> cameras;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
