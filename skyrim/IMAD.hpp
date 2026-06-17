#ifndef IMAD_HPP
#define IMAD_HPP

#include "core.hpp"
#include "base_types.hpp"

struct IMADPair {
    float timestamp;
    float value;
};

class IMAD : public Record {
public:
    static const RecordSchema schema;
    zstring editorId;
    uint32 flag;
    float duration;
    std::vector<uint32> timeEntries;
    std::vector<IMADPair> blur;
    std::vector<IMADPair> doubleVision;
    std::vector<float> tint;
    std::vector<float> fade;
    std::vector<IMADPair> radialBlurStr;
    std::vector<IMADPair> radialBlurRampup;
    std::vector<IMADPair> radialBlurStart;
    std::vector<IMADPair> radialBlurRampdown;
    std::vector<IMADPair> radialBlurDownStart;
    std::vector<IMADPair> depthOfFieldStrength;
    std::vector<IMADPair> depthOfFieldDistance;
    std::vector<IMADPair> depthOfFieldRange;
    std::vector<IMADPair> fullScreenMotionBlur;
    std::vector<IMADPair> eyeAdaptSpeedMultiply;
    std::vector<IMADPair> eyeAdaptSpeedAdd;
    std::vector<IMADPair> bloomBlurRadiusMultiply;
    std::vector<IMADPair> bloomBlurRadiusAdd;
    std::vector<IMADPair> bloomThresholdMultiply;
    std::vector<IMADPair> bloomThresholdAdd;
    std::vector<IMADPair> bloomScaleMultiply;
    std::vector<IMADPair> bloomScaleAdd;
    std::vector<IMADPair> targetLumMinMultiply;
    std::vector<IMADPair> targetLumMinAdd;
    std::vector<IMADPair> targetLumMaxMultiply;
    std::vector<IMADPair> targetLumMaxAdd;
    std::vector<IMADPair> sunlightScaleMultiply;
    std::vector<IMADPair> sunlightScaleAdd;
    std::vector<IMADPair> skyScaleMultiply;
    std::vector<IMADPair> skyScaleAdd;
    std::vector<IMADPair> unknown1;
    std::vector<IMADPair> unknown2;
    std::vector<IMADPair> unknown3;
    std::vector<IMADPair> unknown4;
    std::vector<IMADPair> unknown5;
    std::vector<IMADPair> unknown6;
    std::vector<IMADPair> unknown7;
    std::vector<IMADPair> unknown8;
    std::vector<IMADPair> unknown9;
    std::vector<IMADPair> unknown10;
    std::vector<IMADPair> saturationMultiply;
    std::vector<IMADPair> saturationAdd;
    std::vector<IMADPair> brightnessMultiply;
    std::vector<IMADPair> brightnessAdd;
    std::vector<IMADPair> contrastMultiply;
    std::vector<IMADPair> contrastAdd;
    std::vector<IMADPair> unknown11;
    std::vector<IMADPair> unknown12;

    IMAD() : Record("IMAD") {}
    const RecordSchema& getSchema() const override { return schema; }
    void populate(std::istream& is) override;
    bool validate() override;
};

#endif
