#include "illuminate.hpp"

TEST_CASE(EXPECT_GT) {
    EXPECT_GT(2+2,1+1)
    EXPECT_GT(2+2,2+2)
    EXPECT_GT(1+1,2+2)
}
