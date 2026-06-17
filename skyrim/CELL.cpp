#include "CELL.hpp"
#include <cstring>

const RecordSchema CELL::schema = {
    {
        FieldSchema{"EDID", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->edid.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"FULL", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->full.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->data = static_cast<NumericField<uint16>*>(f)->value;
        }},
        FieldSchema{"XCLC", 1, 1, [](Record* r, Field* f) {
            // XCLC: int32 X, int32 Y, uint32 flags
        }},
        FieldSchema{"XCLL", 1, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<CELL*>(r)->xcll, f->raw_data.data(), std::min((size_t)92, f->raw_data.size()));
        }},
        FieldSchema{"TVDT", 1, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<CELL*>(r)->tvdt, f->raw_data.data(), std::min((size_t)684, f->raw_data.size()));
        }},
        FieldSchema{"MHDT", 1, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<CELL*>(r)->mhdt, f->raw_data.data(), std::min((size_t)1028, f->raw_data.size()));
        }},
        FieldSchema{"XCGD", 0, 1, [](Record* r, Field* f) {}},
        FieldSchema{"LTMP", 0, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->ltmp = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"LNAM", 1, 1, [](Record* r, Field* f) {
            std::memcpy(static_cast<CELL*>(r)->lnam, f->raw_data.data(), std::min((size_t)4, f->raw_data.size()));
        }},
        FieldSchema{"XCLW", 0, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xclw = static_cast<NumericField<float>*>(f)->value;
        }},
        FieldSchema{"XNAM", 1, 1, [](Record* r, Field* f) {
            if (!f->raw_data.empty()) static_cast<CELL*>(r)->xnam = f->raw_data[0];
        }},
        FieldSchema{"XCLR", 1, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / sizeof(FormID);
            for (size_t i = 0; i < count; ++i) {
                FormID fid;
                std::memcpy(&fid, f->raw_data.data() + i * sizeof(FormID), sizeof(FormID));
                static_cast<CELL*>(r)->xclr.push_back(fid);
            }
        }},
        FieldSchema{"XLCN", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xlcn = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XWCS", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xwcs = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"XWCN", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xwcn = static_cast<NumericField<uint32>*>(f)->value;
        }},
        FieldSchema{"XWCU", 1, 1, [](Record* r, Field* f) {
            size_t count = f->raw_data.size() / 16;
            for (size_t i = 0; i < count; ++i) {
                for (int j = 0; j < 16; ++j) {
                    static_cast<CELL*>(r)->xwcu.push_back(f->raw_data[i * 16 + j]);
                }
            }
        }},
        FieldSchema{"XCWT", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xcwt = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XOWN", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xown = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XILL", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xill = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XWEM", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xwem.value = static_cast<ZStringField*>(f)->value;
        }},
        FieldSchema{"XCCM", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xccm = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XCAS", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xcas = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XEZN", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xezn = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XCMO", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xcmo = static_cast<NumericField<FormID>*>(f)->value;
        }},
        FieldSchema{"XCIM", 1, 1, [](Record* r, Field* f) {
            static_cast<CELL*>(r)->xcim = static_cast<NumericField<FormID>*>(f)->value;
        }},
    }
};

void CELL::populate(std::istream& is) {
    Record::populate(is);
}

bool CELL::validate() {
    return Record::validate();
}
