#ifndef CORE_HPP
#define CORE_HPP

#include "base_types.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <istream>
#include <ostream>
#include <variant>
#include <functional>
#include <optional>
#include <cstring>

const int UNLIMITED = -1;

class Record;
class Field;

class Form {
public:
    std::string type;
    Form(const std::string& t) : type(t) {}
    virtual ~Form() = default;

    static std::string read_zstring(std::istream& is, uint16_t length);
};

struct FieldSchema {
    std::string type;
    int min = 0;
    int max = UNLIMITED;
    std::function<void(Record*, Field*)> assign = nullptr;
};

// Forward declaration — SchemaElement uses variant which includes GroupSchema
using SchemaElement = std::variant<FieldSchema, struct GroupSchema>;

struct GroupSchema {
    std::vector<SchemaElement> members;
    int min = 0;
    int max = UNLIMITED;
    std::function<void(Record*, const std::vector<Field*>&)> assign = nullptr;
};

struct RecordSchema {
    std::vector<SchemaElement> elements;
    RecordSchema(std::initializer_list<SchemaElement> elems) : elements(elems) {}
};

class Field : public Form {
public:
    uint16_t length = 0;
    std::vector<uint8_t> raw_data;
    Field(const std::string& t) : Form(t) {}
    virtual void populate_from_data() = 0;
    virtual bool validate() { return true; }
    virtual void serialize(std::ostream& os) const = 0;
};

class Record : public Form {
public:
    RecordHeader header;
    std::vector<std::unique_ptr<Field>> fields;
    
    Record(const std::string& t) : Form(t) {}
    
    virtual const RecordSchema& getSchema() const = 0;
    virtual void populate(std::istream& is);
    virtual bool validate() { return true; }
};

class FieldFactory {
public:
    static std::unique_ptr<Field> create(const std::string& type);
    static bool is_raw_field(const std::string& type);
};

class RecordFactory {
public:
    static std::unique_ptr<Record> create(const std::string& type);
};

class ZStringField : public Field {
public:
    std::string value;
    ZStringField(const std::string& t) : Field(t) {}
    void populate_from_data() override;
    void serialize(std::ostream& os) const override;
};

class RawField : public Field {
public:
    RawField(const std::string& t) : Field(t) {}
    void populate_from_data() override { /* raw bytes already in raw_data */ }
    void serialize(std::ostream& os) const override {
        if (!raw_data.empty()) {
            uint16_t len = static_cast<uint16_t>(raw_data.size());
            os.write(reinterpret_cast<const char*>(&len), sizeof(len));
            os.write(reinterpret_cast<const char*>(raw_data.data()), raw_data.size());
        }
    }
};

template <typename T>
class NumericField : public Field {
public:
    T value;
    NumericField(const std::string& t) : Field(t) {}
    void populate_from_data() override {
        if (raw_data.size() >= sizeof(T)) {
            std::memcpy(&value, raw_data.data(), sizeof(T));
        }
    }
    void serialize(std::ostream& os) const override {
        os.write(reinterpret_cast<const char*>(&value), sizeof(T));
    }
};

#endif
