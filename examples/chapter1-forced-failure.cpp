#include "illuminate.hpp"

TEST_CASE(failures) {
    FAIL("You will see this message...")
    FATALLY_FAIL("...and this message...")
    FAIL("...but not this message.")
}
