#include "illuminate.hpp"

TEST_CASE(ASSERT_LT_VAL) {
    ASSERT_LT_VAL(2+2,5)
    ASSERT_LT_VAL(2+2,4)
    ASSERT_LT_VAL(2+2,3)
}
