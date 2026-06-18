#ifndef GMST_HPP
#define GMST_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class GMST : public Record {
public:
    zstring edid;
    std::vector<uint8> data;

    GMST() : Record("GMST") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
