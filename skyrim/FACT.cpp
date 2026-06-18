#include "FACT.hpp"
#include <cstring>

const RecordSchema FACT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"FULL", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto it = std::find(raw.begin(), raw.end(), uint8_t(0x1C));
            rec->full.value = std::string(raw.begin(), it != raw.end() ? it : raw.end());
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->data, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->data));
        }},
        FieldSchema{"XNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            memcpy(&rec->stol, raw.data(), std::min(sizeof(rec->stol), raw.size()));
        }},
        FieldSchema{"JAIL", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->jail, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->jail));
        }},
        FieldSchema{"WAIT", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->wait, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->wait));
        }},
        FieldSchema{"PLCN", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->plcn, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->plcn));
        }},
        FieldSchema{"CRGR", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->crgr, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->crgr));
        }},
        FieldSchema{"JOUT", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->jout, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->jout));
        }},
        FieldSchema{"CRVA", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            for (auto b : raw) rec->crva.push_back(b);
        }},
        FieldSchema{"VEND", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->vend, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->vend));
        }},
        FieldSchema{"VMAD", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            for (size_t i = 0; i < raw.size() && i < 12; ++i) {
                rec->venv[i] = raw[i];
            }
        }},
        FieldSchema{"VNAM", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            memcpy(&rec->venc, static_cast<RawField*>(f)->raw_data.data(), sizeof(rec->venc));
        }},
        FieldSchema{"VENC", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            float val;
            memcpy(&val, static_cast<RawField*>(f)->raw_data.data(), sizeof(val));
            uint8_t* p = reinterpret_cast< uint8_t*>(rec->venv + 8);
            memcpy(p, &val, sizeof(float));
        }},
        FieldSchema{"VENV", 0, 1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            float val;
            memcpy(&val, static_cast<RawField*>(f)->raw_data.data(), sizeof(val));
            uint8_t* p = reinterpret_cast< uint8_t*>(rec->venv + 8);
            if (rec->venv[11] == 0) {
                memcpy(p, &val, sizeof(float));
            }
        }},
        FieldSchema{"PLVD", 0, -1, [](Record* r, Field* f) {
            auto* rec = static_cast<FACT*>(r);
            auto raw = static_cast<RawField*>(f)->raw_data;
            auto sz = std::min(raw.size(), sizeof(rec->plvd));
            memcpy(rec->plvd, raw.data(), sz);
        }},
        FieldSchema{"CTDA", 0, -1, [](Record* r, Field* f) {
            // CTDA is a repeating condition entry — handled as raw data for now
            (void)r; (void)f;
        }},
    }
};
