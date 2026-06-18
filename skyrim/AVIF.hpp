#ifndef AVIF_HPP
#define AVIF_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

struct PerkSection {
    FormID perk;
    uint32 flag;
    uint32 x_coord;
    uint32 y_coord;
    float h_pos;
    float v_pos;
    FormID skill;
    std::vector<uint32> connecting_lines;
    uint32 index_number;
};

class AVIF : public Record {
public:
    zstring editorId;
    lstring name;
    lstring description;
    zstring abbreviation;
    uint32 data;
    float avData[4];
    std::vector<PerkSection> perkTree;

    AVIF() : Record("AVIF") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
