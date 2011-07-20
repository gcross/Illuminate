#include "illuminate.hpp"

TEST_CASE(EXPECT_NE) {
    EXPECT_NE(1+1,2+2)
    EXPECT_NE(1+2,2+1)
    EXPECT_NE(2+1,1+2)
}
