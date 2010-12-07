//@+leo-ver=5-thin
//@+node:gcross.20101205214942.2504: * @thin test2.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205214942.2505: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20101205214942.2506: ** Tests
TEST_SUITE(Suite_1) {
    TEST_SUITE(subSuite_B) {
        TEST_CASE(X) {
            EXPECT_TRUE(false);
            EXPECT_EQ(1,0);
            EXPECT_EQ(0,0);
            EXPECT_TRUE(1 < 0);
        }
    }
}
TEST_SUITE(Suite_2) {
    TEST_SUITE(subSuite) {
        TEST_CASE(X) {
            ASSERT_TRUE(true);
            ASSERT_EQ(1,0);
        }
        TEST_CASE(Y) {
            ASSERT_TRUE(true);
        }
    }
}
//@-others
//@-leo
