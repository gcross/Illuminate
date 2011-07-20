#include "illuminate.hpp"

TEST_CASE(ASSERT_LE) {
    ASSERT_LE(1+1,2+2)
    ASSERT_LE(2+2,2+2)
    ASSERT_LE(2+2,1+1)
    ASSERT_LE(3+3,1+1)
}
