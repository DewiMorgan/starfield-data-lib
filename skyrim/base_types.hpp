#ifndef BASE_TYPES_H
#define BASE_TYPES_H
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <array>

typedef uint32_t FormID;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef float float_t;
struct rgb { uint8 r, g, b, a; };
struct ZString { std::string value; };
typedef ZString zstring;
typedef ZString lstring;
typedef ZString dlstring;

typedef int8_t int8;
typedef int16_t int16;
typedef uint64_t uint64;
typedef FormID formid;

struct RecordHeader {
    char type[4];
    uint32_t payload_length;
    uint32_t flags;
    uint32_t formid;
    uint16_t timestamp;
    uint16_t vc;
    uint16_t version;
    uint16_t unknown;
};

struct GroupHeader {
    char type[4];
    uint32_t total_size;
    char label[4];
    int32_t group_type;
    uint16_t timestamp;
    uint16_t vc;
    uint32_t unknown;
};

struct FieldHeader {
    char type[4];
    uint16_t length;
};

// Placeholder data structs

struct BookData { std::string value; };
struct CLASData { std::string value; };
struct CLMTSunMoon { std::string value; };
struct CONTData { std::string value; };
struct CRDT { std::string value; };
struct CamData { std::string value; };
struct DIALData { std::string value; };
struct DODT { std::string value; };
struct DUALData { std::string value; };
struct EAMT { std::string value; };
struct EFSHData { std::string value; };
struct EITM { std::string value; };
struct ENIT { std::string value; };
struct ETYP { std::string value; };
struct EXPLData { std::string value; };
struct FACTCrimeGold { std::string value; };
struct FACTPlayerLvd { std::string value; };
struct FACTVendorVenv { std::string value; };
struct FSTSSetCount { std::string value; };
struct FURNWorkbenchData { std::string value; };
struct GMSTValue { std::string value; };
struct GRASData { std::string value; };
struct HAZDData { std::string value; };
struct ICO2 { std::string value; };
struct IDLEData { std::string value; };
struct IMADData { std::string value; };
struct INFOData { std::string value; };
struct INGREnchantedItem { std::string value; };
struct INGRItemData { std::string value; };
struct IPCTData { std::string value; };
struct IPCTDecalData { std::string value; };
struct KEYMItemData { std::string value; };
struct LCTNEncounter { std::string value; };
struct LGTMColors { std::string value; };
struct LGTMLighting { std::string value; };
struct LIGHData { std::string value; };
struct LString { std::string value; };
struct MATOData { std::string value; };
struct MGEFData { std::string value; };
struct MIC2 { std::string value; };
struct MISCItemData { std::string value; };
struct MNAM { std::string value; };
struct MOVTAnimThresholds { std::string value; };
struct MOVTDefaultData { std::string value; };
struct MUSCData { std::string value; };
struct MUSTLoopData { std::string value; };
struct NPCBaseStats { std::string value; };
struct NPCsAIData { std::string value; };
struct NPCsFaceMorphs { std::string value; };
struct NPCsSkillStatData { std::string value; };
struct NPCsSkinTone { std::string value; };
struct SPIT { std::string value; };
struct XCGD { std::string value; };
struct XCLC { std::string value; };
struct XCLL { std::string value; };
struct XRMR { std::string value; };

struct Master { ZString name; };
struct HEDR { uint32_t magic; uint32_t version; uint32_t size; };
struct CloudTextureColor { std::string value; };
struct CloudTextureAlpha { std::string value; };
struct ColorDefinition { std::string value; };
struct AmbientSound { std::string value; };
struct LightingData { std::string value; };
#endif
