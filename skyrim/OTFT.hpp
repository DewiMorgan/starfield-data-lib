#ifndef OTFT_H
#define OTFT_H

#include "base_types.hpp"
#include "core.hpp"
#include <vector>

struct OTFT : public Record {
    ZString editorId;
    std::vector<FormID> inventoryList;  // ITMZ: repeating formid[]

    static const RecordSchema schema;
    const RecordSchema& getSchema() const override;
    bool validate() override;
};

#endif
