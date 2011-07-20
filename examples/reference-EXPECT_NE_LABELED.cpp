#include "illuminate.hpp"

TEST_CASE(EXPECT_NE_LABELED) {
    EXPECT_NE_LABELED("first value",1,"second value",2)
    EXPECT_NE_LABELED("first value",1,"second value",1)
    EXPECT_NE_LABELED("first value",0,"second value",0)
}
