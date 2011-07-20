#include "illuminate.hpp"

TEST_CASE(EXPECT_LE) {
    EXPECT_LE(1+1,2+2)
    EXPECT_LE(2+2,2+2)
    EXPECT_LE(2+2,1+1)
    EXPECT_LE(3+3,1+1)
}
