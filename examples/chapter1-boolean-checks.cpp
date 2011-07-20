#include "illuminate.hpp"

TEST_CASE(two_plus_two_test) {
    EXPECT_TRUE(2+2==4)
    EXPECT_TRUE(2+2==5)
    EXPECT_FALSE(2+2==4)
    EXPECT_FALSE(2+2==5)
}
