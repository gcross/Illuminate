#include "illuminate.hpp"

TEST_CASE(EXPECT_FALSE) {
    EXPECT_FALSE(1+1 == 2)
    EXPECT_FALSE(2+2 == 4)
    EXPECT_FALSE(1+1 == 3)
    EXPECT_FALSE(2+2 == 5)
}
