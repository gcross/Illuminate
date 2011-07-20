#include "illuminate.hpp"

TEST_CASE(EXPECT_EQ_VAL) {
    EXPECT_EQ_VAL(2+2,4)
    EXPECT_EQ_VAL(2+2,5)
    EXPECT_EQ_VAL(2+2,6)
}
