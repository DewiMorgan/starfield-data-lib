#include "MESG.hpp"
#include <cstring>

const RecordSchema MESG::schema = {
    {
        // EDID (+) - required zstring
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<MESG*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        // DESC (+) - required lstring (0x1C delimiter)
        FieldSchema{"DESC", 1, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<MESG*>(r);
            auto& raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->messageText.value = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        // FULL (-) - optional lstring (0x1C delimiter)
        FieldSchema{"FULL", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<MESG*>(r);
            auto& raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->title.value = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        // INAM (-) - optional uint32 (always 0)
        FieldSchema{"INAM", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MESG*>(r)->unknown;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // QNAM (-) - optional formid
        FieldSchema{"QNAM", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MESG*>(r)->quest;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // DNAM (+) - required uint32 flags
        FieldSchema{"DNAM", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MESG*>(r)->flags;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // TNAM (-) - optional uint32 time
        FieldSchema{"TNAM", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MESG*>(r)->time;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // CTDA (*) - repeating condition data block
        FieldSchema{"CTDA", 0, -1, [](Record* r, Field* f) {
            static_cast<MESG*>(r)->conditionData.insert(
                static_cast<MESG*>(r)->conditionData.end(),
                static_cast<RawField*>(f)->raw_data.begin(),
                static_cast<RawField*>(f)->raw_data.end()
            );
        }},
        // ITXT (*) - repeating lstring response texts (0x1C delimiter)
        FieldSchema{"ITXT", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<MESG*>(r);
            auto& raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->responseTexts.push_back(std::string(raw.begin(), it != raw.end() ? it : raw.end()));
        }},
    }
};
