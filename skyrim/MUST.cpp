#include "MUST.hpp"
#include <cstring>

const RecordSchema MUST::schema = {
    {
        // EDID (+) - required zstring
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<MUST*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        // CNAM (+) - required uint32 (track type identifier)
        FieldSchema{"CNAM", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->trackType;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // FLTV (-) - optional float (duration in seconds)
        FieldSchema{"FLTV", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->duration;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // DNAM (-) - optional float (fade-out in seconds)
        FieldSchema{"DNAM", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->fadeOut;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // ANAM (-) - optional zstring (path to .wav)
        FieldSchema{"ANAM", 0, 1, [](Record* r, Field* f) {
            static_cast<MUST*>(r)->trackA.value = static_cast<ZStringField*>(f)->value;
        }},
        // BNAM (-) - optional zstring (path to .wav)
        FieldSchema{"BNAM", 0, 1, [](Record* r, Field* f) {
            static_cast<MUST*>(r)->trackB.value = static_cast<ZStringField*>(f)->value;
        }},
        // FNAM (-) - optional float[] (cue points), may repeat
        FieldSchema{"FNAM", 0, -1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->cuePoints;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(float)) {
                float val;
                memcpy(&val, raw.data(), sizeof(val));
                rec.push_back(val);
            }
        }},
        // SNAM (-) - optional formid[], may repeat
        FieldSchema{"SNAM", 0, -1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->tracks;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(FormID)) {
                FormID fid;
                memcpy(&fid, raw.data(), sizeof(fid));
                rec.push_back(fid);
            }
        }},
        // LNAM (-) - optional 12-byte loop data struct
        FieldSchema{"LNAM", 0, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->loopData;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // CITC (+) - required uint32 (condition count)
        FieldSchema{"CITC", 1, 1, [](Record* r, Field* f) {
            auto& rec = static_cast<MUST*>(r)->conditionCount;
            auto& raw = static_cast<RawField*>(f)->raw_data;
            if (raw.size() >= sizeof(rec)) {
                memcpy(&rec, raw.data(), sizeof(rec));
            }
        }},
        // CTDA (*) - repeating condition entries
        FieldSchema{"CTDA", 0, -1, [](Record* r, Field* f) {
            (void)r; (void)f;
            // CTDA conditions parsed as raw for now; full parsing is record-specific
        }},
    }
};
