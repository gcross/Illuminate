//@+leo-ver=5-thin
//@+node:gcross.20101205214942.1329: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205214942.1340: ** << Includes >>
#include <iostream>

#include "illuminate.hpp"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101205214942.1927: ** Tests
TEST_SUITE(Suite_1) {
    TEST_SUITE(subSuite_A) {
        TEST_CASE(X) {
            FAIL("Failure 1");
            FATALLY_FAIL("Failure 2");
            FAIL("Failure 3");
        }
    }
}
TEST_SUITE(Suite_2) {
    TEST_SUITE(subSuite) {
        TEST_CASE(X) {
            EXPECT_TRUE(false);
            EXPECT_TRUE(0 < 1);
            EXPECT_TRUE(1 < 0);
            ASSERT_TRUE(0 < 1);
            ASSERT_TRUE(1 < 0);
            cout << "Should never be seen!" << endl;
        }
    }
}
//@-others
//@-leo
