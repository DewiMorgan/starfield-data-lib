#ifndef DIAL_HPP
#define DIAL_HPP

#include "core.hpp"
#include "base_types.hpp"

class DIAL : public Record {
public:
    zstring editorId;
    dlstring playerDialogue;
    float priority;
    formid owningBranch;
    formid owningQuest;
    DIALData data;
    char subtype[4];
    uint32 infoCount;

    DIAL() : Record("DIAL") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
