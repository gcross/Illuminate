#include "illuminate.hpp"

TEST_CASE(ASSERT_NE_VAL) {
    ASSERT_NE_VAL(2+2,5)
    ASSERT_NE_VAL(2+2,4)
    ASSERT_NE_VAL(2+1,3)
}
