#ifndef MESG_H
#define MESG_H

#include "base_types.hpp"
#include <vector>

struct MESG : public Record {
    ZString editorId;
    ZString messageText;  // lstring stored via RawField, parsed as string
    ZString title;        // lstring
    uint32 unknown = 0;   // INAM
    FormID quest = 0;     // QNAM
    uint32 flags = 0;     // DNAM
    uint32 time = 0;      // TNAM
    std::vector<uint8_t> conditionData;  // raw CTDA data bytes
    std::vector<std::string> responseTexts;  // ITXT entries (lstrings)

    static const RecordSchema schema;
};

#endif
