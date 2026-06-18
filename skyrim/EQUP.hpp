#ifndef EQUP_HPP
#define EQUP_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class EQUP : public Record {
public:
    zstring editorId;
    std::vector<formid> equipSlots;
    bool useAllParents;

    EQUP() : Record("EQUP") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
