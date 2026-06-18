#ifndef CLAS_HPP
#define CLAS_HPP

#include "core.hpp"
#include "base_types.hpp"

class CLAS : public Record {
public:
    zstring editorId;
    std::string full;
    std::string desc;
    zstring icon;
    uint8_t data[36];

    CLAS() : Record("CLAS") {}
    const RecordSchema& getSchema() const override { return schema; }
    static const RecordSchema schema;
};

#endif
