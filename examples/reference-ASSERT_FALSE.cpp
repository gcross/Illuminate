#include "illuminate.hpp"

TEST_CASE(ASSERT_FALSE) {
    ASSERT_FALSE(1+1 == 2)
    ASSERT_FALSE(2+2 == 4)
    ASSERT_FALSE(1+1 == 3)
    ASSERT_FALSE(2+2 == 5)
}
