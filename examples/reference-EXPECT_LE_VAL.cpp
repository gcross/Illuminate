#include "illuminate.hpp"

TEST_CASE(EXPECT_LE_VAL) {
    EXPECT_LE_VAL(2+2,5)
    EXPECT_LE_VAL(2+2,4)
    EXPECT_LE_VAL(2+2,3)
    EXPECT_LE_VAL(2+2,2)
}
