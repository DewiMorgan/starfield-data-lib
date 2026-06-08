#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

namespace fs = std::filesystem;

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, void(*)(FILE*)> pipe(popen(cmd, "r"), [](FILE* f) { if (f) pclose(f); });
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

TEST_CASE("High-Level Tool Integration") {
    const std::string reader_bin = "./bin/starfield_reader";
    const std::string search_bin = "./bin/sdl_search";
    const std::string bulk_bin = "./bin/sdl_bulk_dump";
    
    // Ensure binaries exist before running tests
    REQUIRE(fs::exists(reader_bin));
    REQUIRE(fs::exists(search_bin));
    REQUIRE(fs::exists(bulk_bin));

    // Pre-flight: Ensure the test database exists
    // We use the credentials from db.conf (root/root)
    exec("mysql -u root -proot -e 'CREATE DATABASE IF NOT EXISTS starfield_test;'");

    SUBCASE("Golden File - End-to-End") {
        const std::string golden_esm = "test/core/golden_test.esm";
        REQUIRE(fs::exists(golden_esm));

        // 1. Index the golden file into the test database
        std::string index_cmd = "MYSQL_DB=starfield_test " + bulk_bin + " " + golden_esm;
        std::string index_output = exec(index_cmd.c_str());
        
        // 2. Search for the known EDID
        std::string search_cmd = "MYSQL_DB=starfield_test " + search_bin + " --edid GoldenQuest";
        std::string search_output = exec(search_cmd.c_str());
        
        CHECK(!search_output.empty());
        CHECK(search_output.find("GoldenQuest") != std::string::npos);
        CHECK(search_output.find("The Golden Quest") != std::string::npos);
        CHECK(search_output.find("SNCU") != std::string::npos);
    }

    SUBCASE("Real-world File - CwLemonade.esm") {
        const std::string esm_path = "/mnt/c/Games/Steam/steamapps/common/Starfield/Data/CwLemonade.esm";
        if (!fs::exists(esm_path)) {
            std::string msg = "Skipping CwLemonade.esm tests: file not found at " + esm_path;
            MESSAGE(msg);
            return;
        }

        SUBCASE("starfield_reader --index") {
            std::string cmd = reader_bin + " " + esm_path + " --index";
            std::string output = exec(cmd.c_str());
            CHECK(output.find("INSERT INTO edids") != std::string::npos);
            CHECK(output.find("SE_FAB25") != std::string::npos);
        }

        SUBCASE("starfield_reader --dump") {
            // Using offset 1163 from SE_FAB25
            std::string cmd = reader_bin + " " + esm_path + " --dump 1163";
            std::string output = exec(cmd.c_str());
            CHECK(!output.empty());
            bool found_qust = output.find("QUST") != std::string::npos;
            bool found_offset = output.find("Offset: 1163") != std::string::npos;
            bool combined = found_qust || found_offset;
            CHECK(combined == true);
        }

        SUBCASE("sdl_search end-to-end") {
            // 1. Index the file into the test database
            std::string index_cmd = "MYSQL_DB=starfield_test " + bulk_bin + " " + esm_path;
            exec(index_cmd.c_str());
            
            // 2. Search for the known EDID
            std::string search_cmd = "MYSQL_DB=starfield_test " + search_bin + " --edid SE_FAB25";
            std::string search_output = exec(search_cmd.c_str());
            
            CHECK(!search_output.empty());
            CHECK(search_output.find("SE_FAB25") != std::string::npos);
            CHECK(search_output.find("QUST") != std::string::npos);
        }
    }
}
