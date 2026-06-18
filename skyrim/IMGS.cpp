#include "IMGS.hpp"
#include <cstring>

const RecordSchema IMGS::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<IMGS*>(r)->editorId.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"ENAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMGS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count && i < 14; ++i) {
                memcpy(&rec->unknown[i], raw.data() + i * sizeof(float), sizeof(float));
            }
        }},
        FieldSchema{"HNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMGS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count && i < 9; ++i) {
                memcpy(&rec->hdrParameters[i], raw.data() + i * sizeof(float), sizeof(float));
            }
        }},
        FieldSchema{"CNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMGS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count && i < 3; ++i) {
                memcpy(&rec->cinematicParameters[i], raw.data() + i * sizeof(float), sizeof(float));
            }
        }},
        FieldSchema{"TNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMGS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count && i < 4; ++i) {
                memcpy(&rec->tintParameters[i], raw.data() + i * sizeof(float), sizeof(float));
            }
        }},
        FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<IMGS*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto count = raw.size() / sizeof(float);
            for (size_t i = 0; i < count && i < 4; ++i) {
                memcpy(&rec->depthOfField[i], raw.data() + i * sizeof(float), sizeof(float));
            }
        }},
    }
};
