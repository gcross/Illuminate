#include "illuminate.hpp"

TEST_CASE(ASSERT_LE_LABELED) {
    ASSERT_LE_LABELED("first value",2,"second value",3)
    ASSERT_LE_LABELED("first value",2,"second value",2)
    ASSERT_LE_LABELED("first value",2,"second value",1)
    ASSERT_LE_LABELED("first value",2,"second value",0)
}
