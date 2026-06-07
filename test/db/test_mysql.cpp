#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mysql_client.h"
#include <fstream>
#include <map>
#include <iostream>

DbConfig readConfig(const std::string& path) {
    DbConfig config;
    std::ifstream file(path);
    std::string line;
    std::map<std::string, std::string> kv;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            kv[line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
    config.host = kv["host"];
    config.user = kv["user"];
    config.pass = kv["pass"];
    config.db = kv["db"];
    return config;
}

TEST_CASE("MySQL Integration Tests") {
    DbConfig config = readConfig("db.conf");
    
    // Use a dedicated test database to avoid polluting production data
    std::string test_db = "starfield_test";
    
    // Temporary config to create the test DB
    DbConfig root_config = config;
    root_config.db = ""; // connect to server
    MySQLClient root_client(root_config);
    
    REQUIRE(root_client.connect() == true);
    root_client.executeQuery("CREATE DATABASE IF NOT EXISTS " + test_db);
    
    // Switch to test DB
    config.db = test_db;
    MySQLClient client(config);
    REQUIRE(client.connect() == true);

    SUBCASE("Source and Asset Management") {
        client.clearDatabase();
        
        // We need to ensure tables exist. In a real scenario, a schema script would run.
        // For the test, we assume the schema is already there or we create a minimal version.
        client.executeQuery("CREATE TABLE IF NOT EXISTS sources (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), path VARCHAR(255))");
        client.executeQuery("CREATE TABLE IF NOT EXISTS assets (id INT AUTO_INCREMENT PRIMARY KEY, source_id INT, virtual_path VARCHAR(255), literal_path VARCHAR(255), internal_path VARCHAR(255), size BIGINT)");
        client.executeQuery("CREATE TABLE IF NOT EXISTS records (id INT AUTO_INCREMENT PRIMARY KEY, source_id INT, offset BIGINT, formid INT, signature VARCHAR(10), size INT)");
        client.executeQuery("CREATE TABLE IF NOT EXISTS edids (id INT AUTO_INCREMENT PRIMARY KEY, source_id INT, offset BIGINT, edid VARCHAR(255))");

        int source_id = client.getOrInsertSource("test_plugin", "/test/path/plugin.esm");
        CHECK(source_id > 0);

        client.insertAsset(source_id, "textures/test.dds", "/test/path/plugin.esm", "textures/test.dds", 1024);
        
        auto res = client.query("SELECT count(*) FROM assets WHERE virtual_path = 'textures/test.dds'");
        REQUIRE(res.size() == 1);
        CHECK(res[0][0] == "1");
    }

    SUBCASE("Batch Operations") {
        client.clearDatabase();
        int source_id = client.getOrInsertSource("batch_test", "/test/batch.esm");
        
        client.beginRecordBatch();
        client.addRecord(source_id, 0x100, 0x12345, "SIG1", 32);
        client.addRecord(source_id, 0x200, 0x67890, "SIG2", 64);
        client.addEdid(source_id, 0x100, "EDID_1");
        client.commitBatch();

        auto records = client.query("SELECT count(*) FROM records");
        REQUIRE(records.size() == 1);
        CHECK(records[0][0] == "2");

        auto edids = client.query("SELECT count(*) FROM edids");
        REQUIRE(edids.size() == 1);
        CHECK(edids[0][0] == "1");
    }
}
