#ifndef OBND_HPP
#define OBND_HPP

#include "core.hpp"

// Object Bounds: 6 floats (minX, minY, minZ, maxX, maxY, maxZ) = 24 bytes
struct OBND : public Field {
    float minX{0}, minY{0}, minZ{0};
    float maxX{0}, maxY{0}, maxZ{0};

    OBND() : Field("OBND") {}

    void populate_from_data() override {
        // raw_data has the 24 bytes already from the parent Field::populate_from_data
        if (raw_data.size() >= 24) {
            std::memcpy(&minX, raw_data.data(), 12);
            std::memcpy(&maxX, raw_data.data() + 12, 12);
        }
    }

    void serialize(std::ostream& os) const override {
        uint8_t buf[24];
        std::memcpy(buf, &minX, 12);
        std::memcpy(buf + 12, &maxX, 12);
        os.write(reinterpret_cast<const char*>(buf), 24);
    }
};

#endif
