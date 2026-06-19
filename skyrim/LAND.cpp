#include "LAND.hpp"
#include <cstring>

const RecordSchema LAND::schema = {
    {
        FieldSchema{"ATXT", 0, -1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            AtxtEntry entry;
            memcpy(&entry.landTexture, f->raw_data.data(), sizeof(FormID));
            entry.quadrant = f->raw_data[4];
            entry.unknown = f->raw_data[5];
            memcpy(&entry.textureLayer, &f->raw_data[6], sizeof(uint16));
            rec->atxtEntries.push_back(entry);
        }},
        FieldSchema{"BTXT", 0, -1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            BtxtEntry entry;
            memcpy(&entry.landTexture, f->raw_data.data(), sizeof(FormID));
            entry.quadrant = f->raw_data[4];
            entry.unk1 = f->raw_data[5];
            entry.unk2 = f->raw_data[6];
            entry.unk3 = f->raw_data[7];
            rec->btxtEntries.push_back(entry);
        }},
        FieldSchema{"DATA", 0, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            memcpy(rec->data, f->raw_data.data(), sizeof(rec->data));
        }},
        FieldSchema{"VCLR", 0, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            memcpy(rec->vclr, f->raw_data.data(), sizeof(rec->vclr));
        }},
        FieldSchema{"VHGT", 0, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            memcpy(rec->vhgt, f->raw_data.data(), sizeof(rec->vhgt));
        }},
        FieldSchema{"VNML", 0, 1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            memcpy(rec->vnml, f->raw_data.data(), sizeof(rec->vnml));
        }},
        FieldSchema{"VTXT", 0, -1, [](Record* r, Field* f) {
            auto rec = static_cast<LAND*>(r);
            // VTXT is a variable-length list of 8-byte records; store the raw block
            for (size_t i = 0; i < f->raw_data.size(); ++i) {
                rec->vtxt[i % sizeof(rec->vtxt)] = f->raw_data[i];
            }
        }},
    }
};
