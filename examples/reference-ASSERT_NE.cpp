#include "illuminate.hpp"

TEST_CASE(ASSERT_NE) {
    ASSERT_NE(1+1,2+2)
    ASSERT_NE(1+2,2+1)
    ASSERT_NE(2+1,1+2)
}
