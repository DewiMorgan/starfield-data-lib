#ifndef DLVW_HPP
#define DLVW_HPP

#include "base_types.hpp"
#include "core.hpp"

struct DLVW : public Record {
    zstring edid;
    FormID qnam;
    std::vector<FormID> bnam; // repeating branches
    std::vector<FormID> tnam; // repeating topics
    uint32 enam;
    uint8 dnam;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif