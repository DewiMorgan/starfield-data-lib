#ifndef BYTE_HPP
#define BYTE_HPP

#include "core.hpp"

// BYTE: Single raw byte field — inherits from RawField for automatic populate_from_data() and serialize()
struct BYTE : public RawField {
    BYTE() : RawField("BYTE") {}
};

#endif
