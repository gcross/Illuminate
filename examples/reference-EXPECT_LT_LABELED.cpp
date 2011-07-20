#include "illuminate.hpp"

TEST_CASE(EXPECT_LT_LABELED) {
    EXPECT_LT_LABELED("first value",2,"second value",3)
    EXPECT_LT_LABELED("first value",2,"second value",2)
    EXPECT_LT_LABELED("first value",2,"second value",1)
}
