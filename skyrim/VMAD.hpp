#ifndef VMAD_HPP
#define VMAD_HPP

#include "core.hpp"

// VMAD: Papyrus Virtual Machine arguments - variable length binary data containing script names, properties, and fragments.
// Inherits from RawField for automatic populate_from_data() and serialize().
struct VMAD : public RawField {
    VMAD() : RawField("VMAD") {}
};

#endif
