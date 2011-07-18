#include "illuminate.hpp"

TEST_CASE(two_plus_two_equals_many_test) {
    for(unsigned int i = 1; i <= 6; ++i) EXPECT_EQ_VAL(2+2,i)
}
