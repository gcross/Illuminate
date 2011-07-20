#include "illuminate.hpp"

TEST_CASE(EXPECT_TRUE) {
    EXPECT_TRUE(1+1 == 2)
    EXPECT_TRUE(2+2 == 4)
    EXPECT_TRUE(1+1 == 3)
    EXPECT_TRUE(2+2 == 5)
}
