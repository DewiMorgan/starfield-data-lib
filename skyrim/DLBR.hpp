#ifndef DLBR_HPP
#define DLBR_HPP

#include "core.hpp"
#include "base_types.hpp"

class DLBR : public Record {
public:
    static const RecordSchema schema;
    zstring editorId;
    formid qnam;
    uint32 tnam;
    uint32 dnam;
    formid snam;

    DLBR() : Record("DLBR") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
