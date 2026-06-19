#ifndef WOOP_HPP
#define WOOP_HPP

#include "base_types.hpp"
#include "core.hpp"

class WOOP : public Record {
public:
    ZString editorId;
    lstring name;
    lstring translation;

    const RecordSchema& getSchema() const override;
    bool validate() override;

private:
    static const RecordSchema schema;
};

#endif