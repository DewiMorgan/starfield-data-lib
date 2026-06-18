#include "core.hpp"
#include <cstring>
#include "ASTP.hpp"
#include "AVIF.hpp"
#include "CAMS.hpp"
#include "CLAS.hpp"
#include "CLFM.hpp"
#include "CSTY.hpp"
#include "DIAL.hpp"
#include "DOBJ.hpp"
#include "ECZN.hpp"
#include "EQUP.hpp"
#include "EYES.hpp"
#include "FLST.hpp"
#include "FSTP.hpp"
#include "GMST.hpp"
#include "GRUP.hpp"
#include "IMGS.hpp"
#include "IPDS.hpp"
#include "KYWD.hpp"
// I'll add others as I convert them

std::string Form::read_zstring(std::istream& is, uint16_t length) {
    if (length == 0) return "";
    std::vector<char> buffer(length);
    is.read(buffer.data(), length);
    return std::string(buffer.data());
}

void ZStringField::populate_from_data() {
    if (raw_data.empty()) {
        value = "";
    } else {
        size_t len = 0;
        while (len < raw_data.size() && raw_data[len] != 0) {
            len++;
        }
        value = std::string(reinterpret_cast<char*>(raw_data.data()), len);
    }
}

void ZStringField::serialize(std::ostream& os) const {
    uint16_t len = static_cast<uint16_t>(value.size() + 1);
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(value.c_str(), len);
}

std::unique_ptr<Field> FieldFactory::create(const std::string& type) {
    // CNAM means different things in different contexts; always store raw bytes
    if (type == "CNAM") return std::make_unique<RawField>(type);
    
    // All other fields default to ZStringField for now
    return std::make_unique<ZStringField>(type);
}

bool FieldFactory::is_raw_field(const std::string& type) {
    return type == "CNAM";
}

void Record::populate(std::istream& is) {
    uint32_t bytesRead = 0;
    uint32_t totalSize = header.payload_length;

    while (bytesRead < totalSize) {
        FieldHeader fh;
        is.read(reinterpret_cast<char*>(&fh), sizeof(FieldHeader));
        if (is.gcount() < static_cast<std::streamsize>(sizeof(FieldHeader))) break;

        std::string type(fh.type, 4);
        auto field = FieldFactory::create(type);
        if (field) {
            field->length = fh.length;
            field->raw_data.resize(fh.length);
            is.read(reinterpret_cast<char*>(field->raw_data.data()), static_cast<std::streamsize>(fh.length));
            field->populate_from_data();
            
            fields.push_back(std::move(field));
        } else {
            is.seekg(fh.length, std::ios::cur);
        }
        bytesRead += sizeof(FieldHeader) + fh.length;
    }
    const RecordSchema&schema = getSchema();

    // Match FieldSchema elements
    for (const auto& element : schema.elements) {
        if (std::holds_alternative<FieldSchema>(element)) {
            const auto& fs = std::get<FieldSchema>(element);
            for (const auto& f : fields) {
                if (f->type == fs.type) {
                    if (fs.assign) fs.assign(this, f.get());
                }
            }
        } else if (std::holds_alternative<GroupSchema>(element)) {
            // Match ordered group members sequentially against fields
            const auto& gs = std::get<GroupSchema>(element);
            size_t fieldIdx = 0;
            for (size_t gi = 0; gi < gs.members.size() && fieldIdx < fields.size(); ++gi) {
                if (std::holds_alternative<FieldSchema>(gs.members[gi])) {
                    const auto& fs = std::get<FieldSchema>(gs.members[gi]);
                    while (fieldIdx < fields.size()) {
                        // Collect all consecutive fields of this type into a group vector
                        std::vector<Field*> groupFields;
                        while (fieldIdx < fields.size() && fields[fieldIdx]->type == fs.type) {
                            groupFields.push_back(fields[fieldIdx].get());
                            fieldIdx++;
                        }
                        if (!groupFields.empty() && gs.assign) {
                            // Call group-level assign for this set of fields
                        }
                    }
                }
            }
        }
    }
}

std::unique_ptr<Record> RecordFactory::create(const std::string& type) {
    if (type == "ASTP") return std::make_unique<ASTP>();
    if (type == "AVIF") return std::make_unique<AVIF>();
    if (type == "CAMS") return std::make_unique<CAMS>();
    if (type == "CLAS") return std::make_unique<CLAS>();
    if (type == "CLFM") return std::make_unique<CLFM>();
    if (type == "CSTY") return std::make_unique<CSTY>();
    if (type == "DIAL") return std::make_unique<DIAL>();
    if (type == "DOBJ") return std::make_unique<DOBJ>();
    if (type == "ECZN") return std::make_unique<ECZN>();
    if (type == "EQUP") return std::make_unique<EQUP>();
    if (type == "EYES") return std::make_unique<EYES>();
    if (type == "FLST") return std::make_unique<FLST>();
    if (type == "FSTP") return std::make_unique<FSTP>();
    if (type == "GMST") return std::make_unique<GMST>();
    if (type == "GRUP") return std::make_unique<GRUP>();
    if (type == "IMGS") return std::make_unique<IMGS>();
    if (type == "IPDS") return std::make_unique<IPDS>();
    if (type == "KYWD") return std::make_unique<KYWD>();
    return nullptr;
}
