#include "illuminate.hpp"

TEST_CASE(EXPECT_GT_LABELED) {
    EXPECT_GT_LABELED("first value",2,"second value",1)
    EXPECT_GT_LABELED("first value",2,"second value",2)
    EXPECT_GT_LABELED("first value",2,"second value",3)
}
