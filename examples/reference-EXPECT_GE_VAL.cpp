#include "illuminate.hpp"

TEST_CASE(EXPECT_GE_VAL) {
    EXPECT_GE_VAL(2+2,3)
    EXPECT_GE_VAL(2+2,4)
    EXPECT_GE_VAL(2+2,5)
    EXPECT_GE_VAL(2+2,6)
}
