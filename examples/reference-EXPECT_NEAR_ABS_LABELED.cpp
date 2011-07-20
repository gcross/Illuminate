#include "illuminate.hpp"

TEST_CASE(EXPECT_NEAR_ABS_LABELED) {
    EXPECT_NEAR_ABS_LABELED("first value",1,"second value",1,1)
    EXPECT_NEAR_ABS_LABELED("first value",1,"second value",2,1)
    EXPECT_NEAR_ABS_LABELED("first value",1,"second value",3,1)
    EXPECT_NEAR_ABS_LABELED("first value",1,"second value",4,1)
}
