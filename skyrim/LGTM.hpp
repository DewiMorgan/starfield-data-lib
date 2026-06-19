#ifndef LGTM_HPP
#define LGTM_HPP

#include "core.hpp"
#include "base_types.hpp"

struct LGTM : public Record {
    // DATA: lighting struct (24 fields total)
    struct LGTMLighting {
        rgb ambientColor;
        rgb directionalColor;
        rgb fogColorNear;
        float fogNear;
        float fogFar;
        uint32 dirRotXY;
        uint32 dirRotZ;
        float dirFade;
        float fogClipDistance;
        float fogPower;
        uint32 unknown[8];  // 8 unknown uint32s
        rgb fogColorFar;
        float fogMax;
        float lightFadeStart;
        float lightFadeEnd;
        uint32 unknown2;    // final unknown
    };

    // DALC: Direct Ambient and Specular Colors
    struct LGTMColors {
        rgb ambientXPlus;
        rgb ambientXMinus;
        rgb ambientYPlus;
        rgb ambientYMinus;
        rgb ambientZPlus;
        rgb ambientZMinus;
        rgb specularColor;
        float fresnelPower;  // 0-1
    };

    ZString editorId;       // EDID: required zstring
    LGTMLighting lighting;   // DATA: required complex struct
    LGTMColors colors;       // DALC: required ambient/specular colors

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override { return schema; }
};


#endif