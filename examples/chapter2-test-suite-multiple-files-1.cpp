#include "illuminate.hpp"

TEST_SUITE(addition_tests) {

  TEST_CASE(one_plus_one_equals_two) {
      EXPECT_EQ_VAL(1+1,2)
  }

}

TEST_SUITE(multiplication_tests) {

  TEST_CASE(one_times_one_equals_one) {
      EXPECT_EQ_VAL(1*1,1)
  }

}
