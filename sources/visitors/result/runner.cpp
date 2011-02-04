//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1615: * @thin runner.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20110203233241.1616: ** << Includes >>
#include "illuminate/visitors/result/runner.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1617: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1618: ** class RunnerResultVisitor
//@+node:gcross.20110203233241.1625: *3* (constructors)
RunnerResultVisitor::RunnerResultVisitor() : number_of_failed_tests(0) {}
//@+node:gcross.20110203233241.1621: *3* test
void RunnerResultVisitor::test(const Test& test) {
    testStarted(test);
    TestResult result = test();
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
