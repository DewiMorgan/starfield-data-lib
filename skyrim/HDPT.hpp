#ifndef HDPT_HPP
#define HDPT_HPP

#include "base_types.hpp"
#include "core.hpp"

struct HDPTOption {
    uint32 optionType;
    zstring triFile;
};

struct HDPT : public Record {
    zstring editorId;
    lstring name;
    zstring model;
    uint8 modelTextureData[12]; // MODT: 12 bytes raw
    uint8 flags;
    uint32 type;
    std::vector<FormID> additionalParts;
    std::vector<HDPTOption> options;
    FormID baseTexture;
    FormID resourceList;
    FormID color;

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};

#endif
