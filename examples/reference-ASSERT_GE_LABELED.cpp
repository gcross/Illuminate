#include "illuminate.hpp"

TEST_CASE(ASSERT_GE_LABELED) {
    ASSERT_GE_LABELED("first value",1,"second value",0)
    ASSERT_GE_LABELED("first value",1,"second value",1)
    ASSERT_GE_LABELED("first value",1,"second value",2)
    ASSERT_GE_LABELED("first value",1,"second value",3)
}
