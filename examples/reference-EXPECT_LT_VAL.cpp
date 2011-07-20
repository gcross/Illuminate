#include "illuminate.hpp"

TEST_CASE(EXPECT_LT_VAL) {
    EXPECT_LT_VAL(2+2,5)
    EXPECT_LT_VAL(2+2,4)
    EXPECT_LT_VAL(2+2,3)
}
