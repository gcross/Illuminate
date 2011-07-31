#include "illuminate.hpp"

TEST_SUITE(Suite) {
  TEST_SUITE(Subsuite) {
    TEST_CASE(Test1) {
      EXPECT_EQ_VAL(1+1,2)
    }
    TEST_CASE(Test2) {
      EXPECT_EQ(1+1,1*1)
      EXPECT_EQ(2+2,2*2)
    }
  }
  TEST_CASE(Test) {
    EXPECT_EQ_VAL(1+1,1)
    EXPECT_EQ_VAL(1+1,2)
    EXPECT_EQ_VAL(1+1,3)
  }
}

TEST_CASE(Test) {
  ASSERT_EQ_LABELED("A",1+1,"B",1)
  ASSERT_EQ_LABELED("A",1+1,"B",2)
  ASSERT_EQ_LABELED("A",1+1,"B",3)
}
