#ifndef EFSH_HPP
#define EFSH_HPP

#include "core.hpp"
#include "base_types.hpp"

class EFSH : public Record {
public:
    static const RecordSchema schema;
    zstring editorId;
    zstring startEffect;
    zstring loopedEffect;
    zstring postEffect;
    zstring loopedGradient;
    zstring endGradient;
    EFSHData data;

    EFSH() : Record("EFSH") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
