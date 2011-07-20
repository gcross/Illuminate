#include "illuminate.hpp"

TEST_CASE(ASSERT_EQ_VAL) {
    ASSERT_EQ_VAL(2+2,4)
    ASSERT_EQ_VAL(2+2,5)
    ASSERT_EQ_VAL(2+2,6)
}
