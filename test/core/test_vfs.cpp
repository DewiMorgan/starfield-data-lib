#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/core/vfs.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

TEST_CASE("MemoryReadStream basic operations") {
    std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE};
    MemoryReadStream stream(data);

    CHECK(stream.size() == 6);
    CHECK(stream.tell() == 0);

    uint8_t buffer[2];
    size_t read = stream.read(buffer, 2);
    CHECK(read == 2);
    CHECK(buffer[0] == 0xDE);
    CHECK(buffer[1] == 0xAD);
    CHECK(stream.tell() == 2);

    stream.seek(4);
    CHECK(stream.tell() == 4);
    read = stream.read(buffer, 2);
    CHECK(read == 2);
    CHECK(buffer[0] == 0xCA);
    CHECK(buffer[1] == 0xFE);
    CHECK(stream.tell() == 6);

    read = stream.read(buffer, 1);
    CHECK(read == 0);
}

TEST_CASE("MemoryReadStream boundaries") {
    std::vector<uint8_t> data = {0x01, 0x02};
    MemoryReadStream stream(data);

    CHECK_THROWS_AS(stream.seek(3), std::out_of_range);
    
    uint8_t buffer[10];
    size_t read = stream.read(buffer, 10);
    CHECK(read == 2);
}

TEST_CASE("FileReadStream basic operations") {
    std::string path = "test_vfs_tmp.bin";
    std::vector<uint8_t> data = {0x11, 0x22, 0x33, 0x44};
    
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(reinterpret_cast<char*>(data.data()), data.size());
    }

    {
        FileReadStream stream(path);
        CHECK(stream.size() == 4);
        
        uint8_t buffer[2];
        size_t read = stream.read(buffer, 2);
        CHECK(read == 2);
        CHECK(buffer[0] == 0x11);
        CHECK(buffer[1] == 0x22);
        
        stream.seek(2);
        read = stream.read(buffer, 2);
        CHECK(read == 2);
        CHECK(buffer[0] == 0x33);
        CHECK(buffer[1] == 0x44);
    }

    std::filesystem::remove(path);
}

TEST_CASE("FileReadStream missing file") {
    CHECK_THROWS_AS(FileReadStream("non_existent_file_12345.bin"), std::runtime_error);
}
