//@+leo-ver=5-thin
//@+node:gcross.20101205214942.2504: * @thin test2.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205214942.2505: ** << Includes >>
#include "illuminate.hpp"
#include "illuminate/visitors/plain_printer.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20101205214942.2506: ** Tests
testSuite(Suite_1) {
    testSuite(subSuite_B) {
        testCase(X) {
            check(false);
            check(1 < 0);
        }
    }
}
testSuite(Suite_2) {
    testSuite(subSuite) {
        testCase(X) {
            assert(true);
        }
    }
}
//@-others
//@-leo
