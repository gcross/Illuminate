#include "illuminate.hpp"

TEST_CASE(ASSERT_GT_VAL) {
    ASSERT_GT_VAL(2+2,3)
    ASSERT_GT_VAL(2+2,4)
    ASSERT_GT_VAL(2+2,5)
}
