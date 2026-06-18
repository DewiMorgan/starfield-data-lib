#ifndef IMGS_HPP
#define IMGS_HPP

#include "core.hpp"
#include "base_types.hpp"

class IMGS : public Record {
public:
    zstring editorId;
    float unknown[14];
    float hdrParameters[9];
    float cinematicParameters[3];
    float tintParameters[4];
    float depthOfField[4];

    IMGS() : Record("IMGS") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
