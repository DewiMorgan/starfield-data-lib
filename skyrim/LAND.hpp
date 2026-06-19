#ifndef LAND_HPP
#define LAND_HPP

#include "core.hpp"
#include "base_types.hpp"

struct LAND : public Record {
    // ATXT entries — each has formid + quadrant + unknown byte + texture layer
    struct AtxtEntry {
        FormID landTexture;  // References LTEX records
        uint8 quadrant;       // 0=BL, 1=BR, 2=UL, 3=UR
        uint8 unknown;
        uint16 textureLayer;  // 0-7
    };
    std::vector<AtxtEntry> atxtEntries;

    // BTXT entries — each has formid + quadrant + 3 unknown bytes
    struct BtxtEntry {
        FormID landTexture;  // References LTEX records (0 = fallback dirt02.dds)
        uint8 quadrant;       // 0=BL, 1=BR, 2=UL, 3=UR
        uint8 unk1, unk2, unk3;
    };
    std::vector<BtxtEntry> btxtEntries;

    uint8 data[4];          // DATA: 4 bytes
    uint8 vclr[3267];       // VCLR: vertex colors
    uint8 vhgt[1096];       // VHGT: vertex heights (33x33 grid + anchor + padding)
    uint8 vnml[3267];       // VNML: vertex normals
    uint8 vtxt[8];          // VTXT: variable list of 8-byte records (parsed into raw blocks)

    static const RecordSchema schema;

    const RecordSchema& getSchema() const override { return schema; }
};

#endif
