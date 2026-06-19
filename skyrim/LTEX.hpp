#ifndef LTEX_HPP
#define LTEX_HPP

#include "core.hpp"

class LTEX : public Record {
public:
    ZString edid;
    FormID tnam;
    FormID mnam;
    std::array<uint8, 2> hnam;
    uint8 snam;
    FormID gnam;
    std::vector<FormID> gras;

    const RecordSchema& getSchema() const override;

private:
    static const RecordSchema schema;
};

#endif