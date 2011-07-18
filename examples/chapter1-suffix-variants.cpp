#include "illuminate.hpp"

TEST_CASE(two_plus_two_equals_four) {
    EXPECT_EQ(2+3,4)
    EXPECT_EQ_LABELED("expression",2+3,"result",4)
    EXPECT_EQ_VAL(2+3,4)
}
