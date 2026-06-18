#ifndef KYWD_HPP
#define KYWD_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class KYWD : public Record {
public:
    zstring editorId;
    rgb color;
    uint32 keywordCount;
    std::vector<FormID> keywords;

    KYWD() : Record("KYWD") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
