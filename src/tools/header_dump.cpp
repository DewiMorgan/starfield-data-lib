#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int main() {
    std::ifstream file("/mnt/c/Games/Steam/steamapps/common/Starfield/Data/Starfield.esm", std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    std::vector<unsigned char> buffer(512);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i] << " ";
        if ((i + 1) % 16 == 0) std::cout << "\n";
    }
    std::cout << std::dec << "\nDone." << std::endl;

    return 0;
}
