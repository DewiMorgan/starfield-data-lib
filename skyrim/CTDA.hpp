#ifndef CTDA_HPP
#define CTDA_HPP

#include "core.hpp"

// CTDA: Condition data field - variable length depending on function used
struct CTDA : public Field {
    uint8 operator_id;
    float comparisonValue;
    uint16 functionIndex;

    CTDA() : Field("CTDA"), operator_id(0), comparisonValue(0), functionIndex(0) {}

    void populate_from_data() override {
        if (raw_data.size() >= 12) {
            std::memcpy(&operator_id, raw_data.data(), 1);
            std::memcpy(&comparisonValue, raw_data.data() + 4, sizeof(float));
            std::memcpy(&functionIndex, raw_data.data() + 8, sizeof(uint16_t));
        }
    }

    void serialize(std::ostream& os) const override {
        uint8_t buf[12];
        std::memcpy(buf, &operator_id, 4); // operator + unknown(3 bytes)
        std::memcpy(buf + 4, &comparisonValue, sizeof(float));
        std::memcpy(buf + 8, &functionIndex, sizeof(uint16_t));
        os.write(reinterpret_cast<const char*>(buf), 12);
        if (raw_data.size() > 12) {
            os.write(reinterpret_cast<const char*>(raw_data.data() + 12), raw_data.size() - 12);
        }
    }
};

#endif
