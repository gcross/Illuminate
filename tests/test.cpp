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
testSuite(Suite_1) {
    testSuite(subSuite_A) {
        testCase(X) {
            fail("Failure 1");
            fatallyFail("Failure 2");
            fail("Failure 3");
        }
    }
}
testSuite(Suite_2) {
    testSuite(subSuite) {
        testCase(X) {
            check(false);
            check(0 < 1);
            check(1 < 0);
            assert_(0 < 1);
            assert_(1 < 0);
            cout << "Should never be seen!" << endl;
        }
    }
}
//@-others
//@-leo
