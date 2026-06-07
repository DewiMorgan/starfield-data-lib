#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Smoke test: Doctest is working") {
    CHECK(1 == 1);
    CHECK(2 != 3);
}
