#include "illuminate.hpp"

TEST_CASE(EXPECT_NEAR_REL) {
    EXPECT_NEAR_REL(2.0,2.0+2.0,1.0)
    EXPECT_NEAR_REL(2.0,3.0+3.0,1.0)
    EXPECT_NEAR_REL(2.0,4.0+4.0,1.0)
    EXPECT_NEAR_REL(2.0,5.0+5.0,1.0)
}
