#ifndef CSTY_HPP
#define CSTY_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class CSTY : public Record {
public:
    zstring editorId;
    std::vector<float> general;
    std::vector<float> melee;
    std::vector<float> closeRange;
    float longRange;
    std::vector<float> flight;
    uint32 flags;

    CSTY() : Record("CSTY") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
