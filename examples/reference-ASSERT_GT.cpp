#include "illuminate.hpp"

TEST_CASE(ASSERT_GT) {
    ASSERT_GT(2+2,1+1)
    ASSERT_GT(2+2,2+2)
    ASSERT_GT(1+1,2+2)
}
