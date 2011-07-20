#include "illuminate.hpp"

TEST_CASE(ASSERT_GE_VAL) {
    ASSERT_GE_VAL(2+2,3)
    ASSERT_GE_VAL(2+2,4)
    ASSERT_GE_VAL(2+2,5)
    ASSERT_GE_VAL(2+2,6)
}
