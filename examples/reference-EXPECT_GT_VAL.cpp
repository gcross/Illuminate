#include "illuminate.hpp"

TEST_CASE(EXPECT_GT_VAL) {
    EXPECT_GT_VAL(2+2,3)
    EXPECT_GT_VAL(2+2,4)
    EXPECT_GT_VAL(2+2,5)
}
