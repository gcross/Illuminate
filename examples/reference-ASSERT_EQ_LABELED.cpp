#include "illuminate.hpp"

TEST_CASE(ASSERT_EQ_LABELED) {
    ASSERT_EQ_LABELED("first value",1,"second value",1)
    ASSERT_EQ_LABELED("first value",1,"second value",2)
    ASSERT_EQ_LABELED("first value",1,"second value",3)
}
