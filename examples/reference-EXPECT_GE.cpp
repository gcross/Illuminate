#include "illuminate.hpp"

TEST_CASE(EXPECT_GE) {
    EXPECT_GE(2+2,1+1)
    EXPECT_GE(1+1,1+1)
    EXPECT_GE(1+1,2+2)
    EXPECT_GE(1+1,1+2)
}
