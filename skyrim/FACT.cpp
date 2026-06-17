#include "FACT.hpp"
#include <cstring>

const RecordSchema FACT::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"FULL", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->full.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"XNAM", 0, UNLIMITED, [](Record* r, Field* f) {}},
        FieldSchema{"DATA", 1, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->data = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"JAIL", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->jail = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"WAIT", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->wait = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"STOL", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->stol = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"PLCN", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->plcn = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"CRGR", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->crgr = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"JOUT", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->jout = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"CRVA", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->crva = f->raw_data;
        }},
        GroupSchema{
            {
                FieldSchema{"RNAM", 1, 1, [](Record* r, Field* f) {}},
                FieldSchema{"MNAM", 1, 1, [](Record* r, Field* f) {}},
                FieldSchema{"FNAM", 1, 1, [](Record* r, Field* f) {}},
            },
            0, UNLIMITED, [](Record* r, const std::vector<Field*>& fields) {
                FACT::Rank rank;
                for (auto* f : fields) {
                    if (f->type == "RNAM") rank.rankId = static_cast<NumericField<uint32>*>(f)->value;
                    else if (f->type == "MNAM") rank.maleTitle.value = static_cast<ZStringField*>(f)->value;
                    else if (f->type == "FNAM") rank.femaleTitle.value = static_cast<ZStringField*>(f)->value;
                }
                static_cast<FACT*>(r)->ranks.push_back(rank);
            }
        },
        FieldSchema{"VEND", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->vend = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"VENC", 0, 1, [](Record* r, Field* f) {
            static_cast<FACT*>(r)->venc = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"VENV", 0, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<FACT*>(r)->venv, f->raw_data.data(), std::min((size_t)12, f->raw_data.size()));
        }},
        FieldSchema{"PLVD", 0, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<FACT*>(r)->plvd, f->raw_data.data(), std::min((size_t)12, f->raw_data.size()));
        }},
        FieldSchema{"CTDA", 0, 1, [](Record* r, Field* f) {}},
    }
};

void FACT::populate(std::istream& is) {
    Record::populate(is);
}

bool FACT::validate() {
    return Record::validate();
}
