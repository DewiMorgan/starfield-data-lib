#include <iostream>
#include "core/schema.hpp"

int main() {
    if (g_RecordSchemas.find("QUST") != g_RecordSchemas.end()) {
        std::cout << "QUST found!" << std::endl;
    } else {
        std::cout << "QUST NOT found!" << std::endl;
    }
    return 0;
}
