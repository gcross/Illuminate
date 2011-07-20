#include "illuminate.hpp"

TEST_CASE(EXPECT_EQ_LABELED) {
    EXPECT_EQ_LABELED("first value",1,"second value",1)
    EXPECT_EQ_LABELED("first value",1,"second value",2)
    EXPECT_EQ_LABELED("first value",1,"second value",3)
}
