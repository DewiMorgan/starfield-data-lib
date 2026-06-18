#ifndef GRUP_HPP
#define GRUP_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class GRUP : public Record {
public:
    char label[4];
    int32 groupType;
    uint16 timestamp;
    uint16 versionControl;
    uint32 unknown;
    std::vector<uint8> records;

    GRUP() : Record("GRUP") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
    static const RecordSchema schema;
};

#endif
