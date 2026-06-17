#ifndef COLL_HPP
#define COLL_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class COLL : public Record {
public:
    static const RecordSchema schema;
    zstring editorId;
    lstring description;
    uint32 uniqueId;
    rgb debugColor;
    uint32 flags;
    zstring name;
    uint32 interactablesCount;
    std::vector<formid> interactables;

    COLL() : Record("COLL") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
