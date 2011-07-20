#include "illuminate.hpp"

TEST_CASE(ASSERT_LE_VAL) {
    ASSERT_LE_VAL(2+2,5)
    ASSERT_LE_VAL(2+2,4)
    ASSERT_LE_VAL(2+2,3)
    ASSERT_LE_VAL(2+2,2)
}
