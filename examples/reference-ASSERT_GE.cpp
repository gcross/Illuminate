#include "illuminate.hpp"

TEST_CASE(ASSERT_GE) {
    ASSERT_GE(2+2,1+1)
    ASSERT_GE(1+1,1+1)
    ASSERT_GE(1+1,2+2)
    ASSERT_GE(1+1,1+2)
}
