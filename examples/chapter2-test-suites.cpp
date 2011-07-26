#include "illuminate.hpp"

TEST_SUITE(addition_tests) {

  TEST_CASE(one_plus_one_equals_two) {
      EXPECT_EQ_VAL(1+1,2)
  }

  TEST_CASE(two_plus_two_equals_four) {
      EXPECT_EQ_VAL(2+2,4)
  }

}

TEST_SUITE(multiplication_tests) {

  TEST_CASE(one_times_one_equals_one) {
      EXPECT_EQ_VAL(1*1,1)
  }

  TEST_CASE(two_times_two_equals_four) {
      EXPECT_EQ_VAL(2*2,4)
  }

}
