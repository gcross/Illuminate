#include "illuminate.hpp"

TEST_CASE(ASSERT_NEAR_ABS_LABELED) {
    ASSERT_NEAR_ABS_LABELED("first value",1,"second value",1,1)
    ASSERT_NEAR_ABS_LABELED("first value",1,"second value",2,1)
    ASSERT_NEAR_ABS_LABELED("first value",1,"second value",3,1)
    ASSERT_NEAR_ABS_LABELED("first value",1,"second value",4,1)
}
