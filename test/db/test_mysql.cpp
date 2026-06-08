#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mock_database.hpp"
#include <iostream>

TEST_CASE("Database Logic Tests (Stubbed)") {
    MockDatabase db;
    
    REQUIRE(db.connect() == true);

    SUBCASE("Source and Asset Management") {
        db.clearDatabase();
        
        int source_id = db.getOrInsertSource("test_plugin", "/test/path/plugin.esm");
        CHECK(source_id > 0);

        db.insertAsset(source_id, "textures/test.dds", "/test/path/plugin.esm", "textures/test.dds", 1024);
        
        auto res = db.query("SELECT count(*) FROM assets WHERE virtual_path = 'textures/test.dds'");
        REQUIRE(res.size() == 1);
        CHECK(res[0][0] == "1");
    }

    SUBCASE("Batch Operations") {
        db.clearDatabase();
        int source_id = db.getOrInsertSource("batch_test", "/test/batch.esm");
        
        db.beginRecordBatch();
        db.addRecord(source_id, 0x100, 0x12345, "SIG1", 32);
        db.addRecord(source_id, 0x200, 0x67890, "SIG2", 64);
        db.addEdid(source_id, 0x100, "EDID_1");
        db.commitBatch();

        auto records = db.query("SELECT count(*) FROM records");
        REQUIRE(records.size() == 1);
        CHECK(records[0][0] == "2");

        auto edids = db.query("SELECT count(*) FROM edids");
        REQUIRE(edids.size() == 1);
        CHECK(edids[0][0] == "1");
    }
}
