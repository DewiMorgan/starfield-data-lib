#include "IMAD.hpp"
#include <cstring>

// Helper to parse standard imad (float pair: timestamp, value) into IMADPair
static void parse_imad_pairs(const std::vector<uint8_t>& data, std::vector<IMADPair>& out) {
    size_t i = 0;
    while (i + 8 <= data.size()) {
        float ts, val;
        memcpy(&ts, &data[i], sizeof(float));
        memcpy(&val, &data[i + 4], sizeof(float));
        i += 8;
        out.push_back({ts, val});
    }
}

// Helper to parse float[5] tuples (timestamp + RGBA) into a flat vector
static void parse_float5_tuples(const std::vector<uint8_t>& data, std::vector<float>& out) {
    size_t i = 0;
    while (i + 20 <= data.size()) {
        for (int j = 0; j < 5; j++) {
            float v;
            memcpy(&v, &data[i], sizeof(float));
            i += 4;
            out.push_back(v);
        }
    }
}

// Helper to parse DNAM: uint32 flag + float duration + uint32[] timeEntries
static void parse_dnam(const std::vector<uint8_t>& data, uint32& flag, float& duration, std::vector<uint32>& timeEntries) {
    if (data.size() < 8) return;
    memcpy(&flag, &data[0], sizeof(uint32));
    memcpy(&duration, &data[4], sizeof(float));
    
    // Remaining bytes are uint32[] time entries
    size_t remaining = data.size() - 8;
    for (size_t i = 0; i + 4 <= remaining; i += 4) {
        uint32 entry;
        memcpy(&entry, &data[8 + i], sizeof(uint32));
        timeEntries.push_back(entry);
    }
}

const RecordSchema IMAD::schema = {
    {
        // EDID - editor ID (zstring)
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<IMAD*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        // DNAM - struct: uint32 flag + float duration + uint32[] timeEntries
        FieldSchema{"DNAM", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMAD*>(r);
            parse_dnam(f->raw_data, rec->flag, rec->duration, rec->timeEntries);
        }},
        // BNAM - blur (imad: float pairs)
        FieldSchema{"BNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->blur);
        }},
        // VNAM - double vision (imad: float pairs)
        FieldSchema{"VNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->doubleVision);
        }},
        // TNAM - tint (float[5] tuples: timestamp + RGBA)
        FieldSchema{"TNAM", 1, 1, [](Record* r, Field* f) {
            parse_float5_tuples(f->raw_data, static_cast<IMAD*>(r)->tint);
        }},
        // NAM3 - fade (float[5] tuples: timestamp + RGBA)
        FieldSchema{"NAM3", 1, 1, [](Record* r, Field* f) {
            parse_float5_tuples(f->raw_data, static_cast<IMAD*>(r)->fade);
        }},
        // RNAM - radial blur str (imad: float pairs)
        FieldSchema{"RNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->radialBlurStr);
        }},
        // SNAM - radial blur rampup (imad: float pairs)
        FieldSchema{"SNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->radialBlurRampup);
        }},
        // UNAM - radial blur start (imad: float pairs)
        FieldSchema{"UNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->radialBlurStart);
        }},
        // NAM1 - radial blur rampdown (imad: float pairs)
        FieldSchema{"NAM1", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->radialBlurRampdown);
        }},
        // NAM2 - radial blur downstart (imad: float pairs)
        FieldSchema{"NAM2", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->radialBlurDownStart);
        }},
        // WNAM - depth of field strength (imad: float pairs)
        FieldSchema{"WNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->depthOfFieldStrength);
        }},
        // XNAM - depth of field distance (imad: float pairs)
        FieldSchema{"XNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->depthOfFieldDistance);
        }},
        // YNAM - depth of field range (imad: float pairs)
        FieldSchema{"YNAM", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->depthOfFieldRange);
        }},
        // NAM4 - fullscreen motion blur (imad: float pairs)
        FieldSchema{"NAM4", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->fullScreenMotionBlur);
        }},
        // ^@IAD - eye adapt speed multiply (imad: float pairs) — byte 0x00 before IAD
        FieldSchema{"^@IAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->eyeAdaptSpeedMultiply);
        }},
        // @IAD - eye adapt speed add (imad: float pairs) — byte 0x40 before IAD
        FieldSchema{"@IAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->eyeAdaptSpeedAdd);
        }},
        // ^AIAD - bloom blur radius multiply (imad: float pairs) — byte 0x41(A) before IAD
        FieldSchema{"^AIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomBlurRadiusMultiply);
        }},
        // AIAD - bloom blur radius add (imad: float pairs)
        FieldSchema{"AIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomBlurRadiusAdd);
        }},
        // ^BIAD - bloom threshold multiply (imad: float pairs)
        FieldSchema{"^BIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomThresholdMultiply);
        }},
        // BIAD - bloom threshold add (imad: float pairs)
        FieldSchema{"BIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomThresholdAdd);
        }},
        // ^CIAD - bloom scale multiply (imad: float pairs)
        FieldSchema{"^CIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomScaleMultiply);
        }},
        // CIAD - bloom scale add (imad: float pairs)
        FieldSchema{"CIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->bloomScaleAdd);
        }},
        // ^DIAD - target lum min multiply (imad: float pairs)
        FieldSchema{"^DIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->targetLumMinMultiply);
        }},
        // DIAD - target lum min add (imad: float pairs)
        FieldSchema{"DIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->targetLumMinAdd);
        }},
        // ^EIAD - target lum max multiply (imad: float pairs)
        FieldSchema{"^EIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->targetLumMaxMultiply);
        }},
        // EIAD - target lum max add (imad: float pairs)
        FieldSchema{"EIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->targetLumMaxAdd);
        }},
        // ^FIAD - sunlight scale multiply (imad: float pairs)
        FieldSchema{"^FIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->sunlightScaleMultiply);
        }},
        // FIAD - sunlight scale add (imad: float pairs)
        FieldSchema{"FIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->sunlightScaleAdd);
        }},
        // ^GIAD - sky scale multiply (imad: float pairs)
        FieldSchema{"^GIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->skyScaleMultiply);
        }},
        // GIAD - sky scale add (imad: float pairs)
        FieldSchema{"GIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->skyScaleAdd);
        }},
        // ^HIAD - unknown (imad: float pairs)
        FieldSchema{"^HIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown1);
        }},
        // HIAD - unknown (imad: float pairs)
        FieldSchema{"HIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown2);
        }},
        // ^IIAD - unknown (imad: float pairs)
        FieldSchema{"^IIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown3);
        }},
        // IIAD - unknown (imad: float pairs)
        FieldSchema{"IIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown4);
        }},
        // ^JIAD - unknown (imad: float pairs)
        FieldSchema{"^JIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown5);
        }},
        // JIAD - unknown (imad: float pairs)
        FieldSchema{"JIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown6);
        }},
        // ^KIAD - unknown (imad: float pairs)
        FieldSchema{"^KIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown7);
        }},
        // KIAD - unknown (imad: float pairs)
        FieldSchema{"KIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown8);
        }},
        // ^LIAD - unknown (imad: float pairs)
        FieldSchema{"^LIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown9);
        }},
        // LIAD - unknown (imad: float pairs)
        FieldSchema{"LIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown10);
        }},
        // ^MIAD - unknown (imad: float pairs)
        FieldSchema{"^MIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown11);
        }},
        // MIAD - unknown (imad: float pairs)
        FieldSchema{"MIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown12);
        }},
        // ^NIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"^NIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown11);
        }},
        // NIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"NIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown12);
        }},
        // ^OIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"^OIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown11);
        }},
        // OIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"OIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown12);
        }},
        // ^PIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"^PIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown11);
        }},
        // PIAD - unknown (imad: float pairs) — may not appear in all files
        FieldSchema{"PIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown12);
        }},
        // ^QIAD - saturation multiply (imad: float pairs)
        FieldSchema{"^QIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->saturationMultiply);
        }},
        // QIAD - saturation add (imad: float pairs)
        FieldSchema{"QIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->saturationAdd);
        }},
        // ^RIAD - brightness multiply (imad: float pairs)
        FieldSchema{"^RIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->brightnessMultiply);
        }},
        // RIAD - brightness add (imad: float pairs)
        FieldSchema{"RIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->brightnessAdd);
        }},
        // ^SIAD - contrast multiply (imad: float pairs)
        FieldSchema{"^SIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->contrastMultiply);
        }},
        // SIAD - contrast add (imad: float pairs)
        FieldSchema{"SIAD", 1, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->contrastAdd);
        }},
        // ^TIAD - unknown (imad: float pairs) — may or may not be present
        FieldSchema{"^TIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown11);
        }},
        // TIAD - unknown (imad: float pairs) — may or may not be present
        FieldSchema{"TIAD", 0, 1, [](Record* r, Field* f) {
            parse_imad_pairs(f->raw_data, static_cast<IMAD*>(r)->unknown12);
        }},
    }
};
