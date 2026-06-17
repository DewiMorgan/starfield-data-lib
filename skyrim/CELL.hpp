#ifndef CELL_HPP
#define CELL_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class CELL : public Record {
public:
    static const RecordSchema schema;
    zstring edid;
    lstring full;
    uint16 data;
    uint8 xclc[12]; // simplified
    uint8 xcll[92]; // simplified
    uint8 tvdt[684];
    uint8 mhdt[1028];
    uint8 xcgd[0]; // variable
    FormID ltmp;
    uint8 lnam[4];
    float xclw;
    uint8 xnam;
    std::vector<FormID> xclr;
    FormID xlcn;
    uint32 xwcs;
    uint32 xwcn;
    std::vector<uint8> xwcu;
    FormID xcwt;
    FormID xown;
    FormID xill;
    zstring xwem;
    FormID xccm;
    FormID xcas;
    FormID xezn;
    FormID xcmo;
    FormID xcim;

    CELL() : Record("CELL") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
