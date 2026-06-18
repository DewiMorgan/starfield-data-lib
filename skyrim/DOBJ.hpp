#ifndef DOBJ_HPP
#define DOBJ_HPP

#include "core.hpp"
#include "base_types.hpp"
#include <vector>

struct DOBJEntry {
    char tag[4];
    FormID formid;
};

class DOBJ : public Record {
public:
    zstring editorId;
    std::vector<DOBJEntry> entries;

    DOBJ() : Record("DOBJ") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
