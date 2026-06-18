#include "GRUP.hpp"
#include <cstring>

const RecordSchema GRUP::schema = {
    {}
};

void GRUP::populate(std::istream&) {
    // GRUP contains Records, not Fields — handled by parse_content in parser.cpp
}

bool GRUP::validate() {
    return true;
}
