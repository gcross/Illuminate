#include "illuminate.hpp"

TEST_CASE(EXPECT_LT) {
    EXPECT_GT(1+1,2+2)
    EXPECT_GT(2+2,2+2)
    EXPECT_GT(2+2,1+1)
}
