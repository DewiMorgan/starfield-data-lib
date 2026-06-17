#include "IMAD.hpp"
#include <cstring>

static void parseImadPairs(Field* f, std::vector<IMADPair>& target) {
    size_t count = f->raw_data.size() / 8;
    for (size_t i = 0; i < count; ++i) {
        IMADPair pair;
        std::memcpy(&pair.timestamp, f->raw_data.data() + i * 8, 4);
        std::memcpy(&pair.value, f->raw_data.data() + i * 8 + 4, 4);
        target.push_back(pair);
    }
}

const RecordSchema IMAD::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<IMAD*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DNAM", 1, 1, [](Record* r, Field* f) {
            uint32 flag;
            float duration;
            std::memcpy(&flag, f->raw_data.data(), 4);
            std::memcpy(&duration, f->raw_data.data() + 4, 4);
            static_cast<IMAD*>(r)->flag = flag;
            static_cast<IMAD*>(r)->duration = duration;
            size_t entriesCount = (f->raw_data.size() - 8) / 4;
            for (size_t i = 0; i < entriesCount; ++i) {
                uint32 entry;
                std::memcpy(&entry, f->raw_data.data() + 8 + i * 4, 4);
                static_cast<IMAD*>(r)->timeEntries.push_back(entry);
            }
        }},
        FieldSchema{"BNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->blur); }},
        FieldSchema{"VNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->doubleVision); }},
        FieldSchema{"TNAM", 0, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / 20;
            for (size_t i = 0; i < count; ++i) {
                for (int j = 0; j < 5; ++j) {
                    float val;
                    std::memcpy(&val, f->raw_data.data() + i * 20 + j * 4, 4);
                    static_cast<IMAD*>(r)->tint.push_back(val);
                }
            }
        }},
        FieldSchema{"NAM3", 0, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / 20;
            for (size_t i = 0; i < count; ++i) {
                for (int j = 0; j < 5; ++j) {
                    float val;
                    std::memcpy(&val, f->raw_data.data() + i * 20 + j * 4, 4);
                    static_cast<IMAD*>(r)->fade.push_back(val);
                }
            }
        }},
        FieldSchema{"RNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->radialBlurStr); }},
        FieldSchema{"SNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->radialBlurRampup); }},
        FieldSchema{"UNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->radialBlurStart); }},
        FieldSchema{"NAM1", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->radialBlurRampdown); }},
        FieldSchema{"NAM2", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->radialBlurDownStart); }},
        FieldSchema{"WNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->depthOfFieldStrength); }},
        FieldSchema{"XNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->depthOfFieldDistance); }},
        FieldSchema{"YNAM", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->depthOfFieldRange); }},
        FieldSchema{"NAM4", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->fullScreenMotionBlur); }},
        FieldSchema{"\x00IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->eyeAdaptSpeedMultiply); }},
        FieldSchema{"\x01IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->eyeAdaptSpeedAdd); }},
        FieldSchema{"\x02IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomBlurRadiusMultiply); }},
        FieldSchema{"\x03IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomBlurRadiusAdd); }},
        FieldSchema{"\x04IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomThresholdMultiply); }},
        FieldSchema{"\x05IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomThresholdAdd); }},
        FieldSchema{"\x06IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomScaleMultiply); }},
        FieldSchema{"\x07IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->bloomScaleAdd); }},
        FieldSchema{"\x08IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->targetLumMinMultiply); }},
        FieldSchema{"\x09IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->targetLumMinAdd); }},
        FieldSchema{"\x0AIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->targetLumMaxMultiply); }},
        FieldSchema{"\x0BIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->targetLumMaxAdd); }},
        FieldSchema{"\x0CIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->sunlightScaleMultiply); }},
        FieldSchema{"\x0DIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->sunlightScaleAdd); }},
        FieldSchema{"\x0EIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->skyScaleMultiply); }},
        FieldSchema{"\x0FIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->skyScaleAdd); }},
        FieldSchema{"\x10IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown1); }},
        FieldSchema{"\x11IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown2); }},
        FieldSchema{"\x12IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown3); }},
        FieldSchema{"\x13IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown4); }},
        FieldSchema{"\x14IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown5); }},
        FieldSchema{"\x15IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown6); }},
        FieldSchema{"\x16IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown7); }},
        FieldSchema{"\x17IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown8); }},
        FieldSchema{"\x18IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown9); }},
        FieldSchema{"\x19IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown10); }},
        FieldSchema{"\x1AIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->saturationMultiply); }},
        FieldSchema{"\x1BIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->saturationAdd); }},
        FieldSchema{"\x1CIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->brightnessMultiply); }},
        FieldSchema{"\x1DIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->brightnessAdd); }},
        FieldSchema{"\x1EIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->contrastMultiply); }},
        FieldSchema{"\x1FIAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->contrastAdd); }},
        FieldSchema{"\x20IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown11); }},
        FieldSchema{"\x21IAD", 0, 1, [](Record* r, Field* f) { parseImadPairs(f, static_cast<IMAD*>(r)->unknown12); }},
    }
};

void IMAD::populate(std::istream& is) {
    Record::populate(is);
}

bool IMAD::validate() {
    return Record::validate();
}
