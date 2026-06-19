#ifndef INFO_HPP
#define INFO_HPP

#include "base_types.hpp"
#include "core.hpp"

struct INFO : public Record {
    zstring edid;
    uint8 vmadRaw[32]; // VMAD: Papyrus script info (approximate size)
    uint16 dialogueTab;
    uint16 flags;
    union {
        float resetTimeFloat; // DATA version
        uint16 resetTimeU16;  // ENAM version
    } resetTime;
    FormID previousInfo;
    uint8 favorLevel;
    std::vector<FormID> topicLinks;
    FormID sharedInfo;
    std::vector<uint8> responseRawData; // raw TRDT responses
    lstring playerResponse;
    FormID speaker;
    FormID walkAwayTopic;
    FormID audioOutputOverride;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
