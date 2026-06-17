#ifndef FACT_HPP
#define FACT_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class FACT : public Record {
public:
    static const RecordSchema schema;
    zstring edid;
    lstring full;
    uint32 data;
    formid jail;
    formid wait;
    formid stol;
    formid plcn;
    formid crgr;
    formid jout;
    std::vector<uint8> crva;
    formid vend;
    formid venc;
    uint8 venv[12];
    uint8 plvd[12];

    struct Rank {
        uint32 rankId;
        lstring maleTitle;
        lstring femaleTitle;
    };
    std::vector<Rank> ranks;

    FACT() : Record("FACT") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
