#ifndef MODL_HPP
#define MODL_HPP

#include "core.hpp"

// MODL is just a zstring field for model filename.
struct MODL : public ZStringField {
    MODL() : ZStringField("MODL") {}
};

#endif
