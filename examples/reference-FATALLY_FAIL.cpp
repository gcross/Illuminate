#include "illuminate.hpp"

TEST_CASE(FATALLY_FAIL) {
    FATALLY_FAIL("First failure message.")
    FATALLY_FAIL("Second failure message.")
}
