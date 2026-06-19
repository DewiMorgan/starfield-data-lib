#ifndef DELM_HPP
#define DELM_HPP

#include "core.hpp"

// DELM: Delimiter marker — no payload data, just marks end of cell section
struct DELM : public Field {
    DELM() : Field("DELM") {}
    
    void populate_from_data() override {
        // DELM has zero-length payload in the binary
    }
    
    void serialize(std::ostream& os) const override {
        uint16_t len = 0;
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    }
};

#endif
