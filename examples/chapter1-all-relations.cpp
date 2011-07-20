#include "illuminate.hpp"

TEST_CASE(two_plus_two_test) {
    for(unsigned int i = 3; i <= 5; ++i) {
        EXPECT_EQ_VAL(2+2,i)
        EXPECT_NE_VAL(2+2,i)
        EXPECT_GE_VAL(2+2,i)
        EXPECT_GT_VAL(2+2,i)
        EXPECT_LE_VAL(2+2,i)
        EXPECT_LT_VAL(2+2,i)
    }
}
