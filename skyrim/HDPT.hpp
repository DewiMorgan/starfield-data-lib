#ifndef HDPT_H
#define HDPT_H

#include "base_types.hpp"
#include <vector>
#include <string>

struct HDPTOption {
    uint32 optionType;
    ZString triFile;
};

struct HDPT {
    zstring editorId;
    lstring name;
    zstring model;
    MODT modelTextureData;
    uint8 flags;
    uint32 type;
    std::vector<FormID> additionalParts;
    std::vector<HDPTOption> options;
    FormID baseTexture;
    FormID resourceList;
    FormID color;
};

#endif
