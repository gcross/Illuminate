#include "illuminate.hpp"

TEST_CASE(EXPECT_LE_LABELED) {
    EXPECT_LE_LABELED("first value",2,"second value",3)
    EXPECT_LE_LABELED("first value",2,"second value",2)
    EXPECT_LE_LABELED("first value",2,"second value",1)
    EXPECT_LE_LABELED("first value",2,"second value",0)
}

