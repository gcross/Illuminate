#include "illuminate.hpp"

TEST_CASE(ASSERT_NE_LABELED) {
    ASSERT_NE_LABELED("first value",1,"second value",2)
    ASSERT_NE_LABELED("first value",1,"second value",1)
    ASSERT_NE_LABELED("first value",0,"second value",0)
}
