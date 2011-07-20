#include "illuminate.hpp"

TEST_CASE(EXPECT_NE_VAL) {
    EXPECT_NE_VAL(2+2,5)
    EXPECT_NE_VAL(2+2,4)
    EXPECT_NE_VAL(2+1,3)
}
