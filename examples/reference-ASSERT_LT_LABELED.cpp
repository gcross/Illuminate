#include "illuminate.hpp"

TEST_CASE(ASSERT_LT_LABELED) {
    ASSERT_LT_LABELED("first value",2,"second value",3)
    ASSERT_LT_LABELED("first value",2,"second value",2)
    ASSERT_LT_LABELED("first value",2,"second value",1)
}
