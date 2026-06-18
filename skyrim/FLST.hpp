#ifndef FLST_HPP
#define FLST_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

class FLST : public Record {
public:
    zstring editorId;
    std::vector<formid> objects;

    FLST() : Record("FLST") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
