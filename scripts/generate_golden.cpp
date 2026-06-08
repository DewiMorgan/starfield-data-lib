#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include "core/parser.hpp"

void writeTlv(std::ofstream& os, const std::string& tag, const std::string& val) {
    os.write(tag.c_str(), tag.size());
    uint32_t len = val.size() + 1; // null term
    os.write(reinterpret_cast<char*>(&len), sizeof(len));
    os.write(val.c_str(), len);
}

void writeTlvFloat(std::ofstream& os, const std::string& tag, float val) {
    os.write(tag.c_str(), tag.size());
    uint32_t len = sizeof(float);
    os.write(reinterpret_cast<char*>(&len), sizeof(len));
    os.write(reinterpret_cast<char*>(&val), sizeof(val));
}

int main() {
    std::ofstream os("test/core/golden_test.esm", std::ios::binary);
    
    std::vector<uint8_t> data;
    auto writeBufTlv = [&](const std::string& tag, const std::string& val) {
        for(char c : tag) data.push_back(c);
        uint16_t len = val.size() + 1;
        for(int i=0; i<2; ++i) data.push_back((len >> (i*8)) & 0xFF);
        for(char c : val) data.push_back(c);
        data.push_back('\0');
    };
    
    auto writeBufTlvFloat = [&](const std::string& tag, float val) {
        for(char c : tag) data.push_back(c);
        uint16_t len = 4;
        for(int i=0; i<2; ++i) data.push_back((len >> (i*8)) & 0xFF);
        for(int i=0; i<4; ++i) data.push_back((reinterpret_cast<uint8_t*>(&val))[i]);
    };

    writeBufTlv("EDID", "GoldenQuest");
    writeBufTlv("FULL", "The Golden Quest");
    
    // We skip SNCU's "On Begin" tags because they aren't 4-char alphanumeric
    // and would cause the current Parser to break and stop indexing.

    RecordHeader h;
    memcpy(h.sig, "SNCU", 4);
    h.dataSize = data.size();
    h.flags = 0;
    h.formId = 0x12345678;
    h.vcs1 = 0;
    h.version = 1;
    h.vcs2 = 0;

    os.write(reinterpret_cast<char*>(&h), sizeof(h));
    os.write(reinterpret_cast<char*>(data.data()), data.size());
    
    return 0;
}
