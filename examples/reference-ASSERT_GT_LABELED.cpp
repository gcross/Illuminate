#include "illuminate.hpp"

TEST_CASE(ASSERT_GT_LABELED) {
    ASSERT_GT_LABELED("first value",2,"second value",1)
    ASSERT_GT_LABELED("first value",2,"second value",2)
    ASSERT_GT_LABELED("first value",2,"second value",3)
}
