//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1587: * @thin test_future.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101208142631.1588: ** << Includes >>
#include "illuminate/visitors/test_future.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1589: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1590: ** class TestFutureVisitor
//@+node:gcross.20101208142631.1591: *3* (constructors)
TestFutureVisitor::TestFutureVisitor(const TestFutures& futures)
    : futures(futures)
    , number_of_failed_tests(0)
{ }
//@+node:gcross.20101208142631.1593: *3* test
void TestFutureVisitor::test(const Test& test) {
    testStarted(test);
    TestResult result = (*futures)[test.id]->get();
    if(result->size() == 0) {
        testPassed(test);
    } else {
        ++number_of_failed_tests;
        testFailed(test,*result);
    }
}
//@-others

}
//@-leo
