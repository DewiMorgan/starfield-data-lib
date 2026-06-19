#include "INFO.hpp"
#include "core.hpp"
#include <cstring>

const RecordSchema INFO::schema = {{
    FieldSchema{"EDID", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->edid.value = static_cast<ZStringField*>(f)->value; }},
    FieldSchema{"VMAD", 0, -1, [](Record* r, Field* f) { std::memcpy(static_cast<INFO*>(r)->vmadRaw, f->raw_data.data(), std::min(static_cast<size_t>(32), f->raw_data.size())); }},
    FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
        if (f->raw_data.size() >= 6) {
            static_cast<INFO*>(r)->dialogueTab = *reinterpret_cast<const uint16*>(f->raw_data.data());
            static_cast<INFO*>(r)->flags = *reinterpret_cast<const uint16*>(f->raw_data.data() + 2);
            std::memcpy(&static_cast<INFO*>(r)->resetTime.resetTimeFloat, f->raw_data.data() + 4, sizeof(float));
        }
    }},
    FieldSchema{"ENAM", 0, 1, [](Record* r, Field* f) {
        if (f->raw_data.size() >= 4) {
            static_cast<INFO*>(r)->flags = *reinterpret_cast<const uint16*>(f->raw_data.data());
            static_cast<INFO*>(r)->resetTime.resetTimeU16 = *reinterpret_cast<const uint16*>(f->raw_data.data() + 2);
        }
    }},
    FieldSchema{"PNAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->previousInfo = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"CNAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->favorLevel = *f->raw_data.data(); }},
    FieldSchema{"TCLT", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->topicLinks.emplace_back(*reinterpret_cast<const FormID*>(f->raw_data.data())); }},
    FieldSchema{"DNAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->sharedInfo = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"RNAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->playerResponse.value = std::string(reinterpret_cast<const char*>(f->raw_data.data()), f->raw_data.size()); }},
    FieldSchema{"ANAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->speaker = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"TWAT", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->walkAwayTopic = *reinterpret_cast<const FormID*>(f->raw_data.data()); }},
    FieldSchema{"ONAM", 0, -1, [](Record* r, Field* f) { static_cast<INFO*>(r)->audioOutputOverride = *reinterpret_cast<const FormID*>(f->raw_data.data()); }}
}};

const RecordSchema& INFO::getSchema() { return schema; }
