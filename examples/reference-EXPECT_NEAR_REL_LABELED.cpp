#include "illuminate.hpp"

TEST_CASE(EXPECT_NEAR_REL_LABELED) {
    EXPECT_NEAR_REL_LABELED("first value",2.0,"second value",4.0,1.0)
    EXPECT_NEAR_REL_LABELED("first value",2.0,"second value",6.0,1.0)
    EXPECT_NEAR_REL_LABELED("first value",2.0,"second value",8.0,1.0)
    EXPECT_NEAR_REL_LABELED("first value",2.0,"second value",10.0,1.0)
}
