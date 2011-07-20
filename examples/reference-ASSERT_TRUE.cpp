#include "illuminate.hpp"

TEST_CASE(ASSERT_TRUE) {
    ASSERT_TRUE(1+1 == 2)
    ASSERT_TRUE(2+2 == 4)
    ASSERT_TRUE(1+1 == 3)
    ASSERT_TRUE(2+2 == 5)
}
