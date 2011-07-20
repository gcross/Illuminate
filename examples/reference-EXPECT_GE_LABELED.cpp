#include "illuminate.hpp"

TEST_CASE(EXPECT_GE_LABELED) {
    EXPECT_GE_LABELED("first value",1,"second value",0)
    EXPECT_GE_LABELED("first value",1,"second value",1)
    EXPECT_GE_LABELED("first value",1,"second value",2)
    EXPECT_GE_LABELED("first value",1,"second value",3)
}
