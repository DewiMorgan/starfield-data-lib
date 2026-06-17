#include "core.hpp"
#include <cstring>

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
    return std::make_unique<ZStringField>(type);
}

void Record::populate(std::istream& is) {
    uint32_t bytesRead = 0;
    uint32_t totalSize = header.payload_length;

    while (bytesRead < totalSize) {
        FieldHeader fh;
        is.read(reinterpret_cast<char*>(&fh), sizeof(FieldHeader));
        if (is.gcount() < sizeof(FieldHeader)) break;

        std::string type(fh.type, 4);
        auto field = FieldFactory::create(type);
        if (field) {
            field->length = fh.length;
            field->raw_data.resize(fh.length);
            is.read(reinterpret_cast<char*>(field->raw_data.data()), fh.length);
            field->populate_from_data();
            
            fields.push_back(std::move(field));
        } else {
            is.seekg(fh.length, std::ios::cur);
        }
        bytesRead += sizeof(FieldHeader) + fh.length;
    }

    const RecordSchema& schema = getSchema();
    for (const auto& element : schema.elements) {
        if (std::holds_alternative<FieldSchema>(element)) {
            const auto& fs = std::get<FieldSchema>(element);
            for (const auto& f : fields) {
                if (f->type == fs.type) {
                    if (fs.assign) fs.assign(this, f.get());
                }
            }
        }
    }
}
