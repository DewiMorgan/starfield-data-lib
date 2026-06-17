#ifndef FSTS_HPP
#define FSTS_HPP

#include "core.hpp"
#include "base_types.hpp"

class FSTS : public Record {
public:
    static const RecordSchema schema;
    zstring editorId;
    FSTSSetCount setCount;
    std::vector<formid> footstepSets;

    FSTS() : Record("FSTS") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
