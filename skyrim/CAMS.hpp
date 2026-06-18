#ifndef CAMS_HPP
#define CAMS_HPP

#include "core.hpp"
#include "base_types.hpp"

class CAMS : public Record {
public:
    zstring editorId;
    zstring model;
    uint8 modelData[12];
    CamData camData;
    formid effect;

    CAMS() : Record("CAMS") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
