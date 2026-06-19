#ifndef MODT_HPP
#define MODT_HPP

#include "core.hpp"

// MODT: Model Texture Data - exactly 12 bytes of raw binary data
struct MODT : public RawField {
    MODT() : RawField("MODT") {}
};

#endif