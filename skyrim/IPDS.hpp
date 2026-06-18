#ifndef IPDS_HPP
#define IPDS_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

struct IPDSPair {
    FormID matt;
    FormID ipct;
};

class IPDS : public Record {
public:
    zstring editorId;
    std::vector<IPDSPair> pairs;

    IPDS() : Record("IPDS") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
