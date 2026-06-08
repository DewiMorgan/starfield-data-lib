#include <iostream>
#include "core/schema.hpp"

int main() {
    if (g_RecordSchemas.find("SNCU") != g_RecordSchemas.end()) {
        std::cout << "SNCU found!" << std::endl;
    } else {
        std::cout << "SNCU NOT found!" << std::endl;
    }
    return 0;
}
