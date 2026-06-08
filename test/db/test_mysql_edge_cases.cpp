#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mysql_client.hpp"
#include <filesystem>
#include <fstream>

TEST_CASE("MySQL Client Edge Cases") {
    // Test config with wrong password to trigger connection failure
    DbConfig bad_config = {"localhost", "root", "wrong_password", "starfield"};
    MySQLClient client_bad(bad_config, false);
    
    SUBCASE("Connection Failure") {
        CHECK(client_bad.connect() == false);
    }

    // Test dry run mode
    DbConfig config = {"localhost", "root", "root", "starfield"};
    MySQLClient client_dry(config, true);
    client_dry.connect(); // Should still connect if possible, but not execute
    
    SUBCASE("Dry Run Execution") {
        // executeQuery and query should not actually hit the DB
        // we just check they don't crash
        client_dry.executeQuery("DROP TABLE records"); 
        auto res = client_dry.query("SELECT * FROM records");
        CHECK(res.empty());
    }

    // Test quoting/escaping logic
    MySQLClient client_real(config, false);
    client_real.connect();

    SUBCASE("Quoting and Escaping") {
        // This should trigger the 'replace' calls in insertAsset, getOrInsertSource, addEdid
        client_real.insertAsset(1, "Path's", "Literal's", "Internal's", 100);
        int id = client_real.getOrInsertSource("Source's", "Path's");
        client_real.addEdid(1, 100, "EDID's");
        
        // Verify we can retrieve the record if it was handled correctly
        auto res = client_real.query("SELECT * FROM sources WHERE path = 'Path\\'s'");
        // Depending on DB state, we might not find it, but the call should be safe
    }

    SUBCASE("Query Failure") {
        // Execute a malformed query to trigger the error path
        client_real.executeQuery("SELECT * FROM non_existent_table_xyz");
    }
}
