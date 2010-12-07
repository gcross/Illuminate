//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1757: * @thin ansi_test_runner.hpp
//@@language cplusplus

#ifndef VISITORS_ANSI_TEST_RUNNER_HPP
#define VISITORS_ANSI_TEST_RUNNER_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1758: ** << Includes >>
#include <iostream>

#include "illuminate.hpp"
#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1759: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1760: ** class ANSITestRunnerVisitor
class ANSITestRunnerVisitor : public IndentedOutputVisitor {
protected:
    int number_of_failed_tests;
    ANSITestRunnerVisitor(ostream& out);
    virtual void suite(const Suite& test);
    virtual void test(Test& test);
public:
    static void runTests(ostream& out=cout);
};
//@-others

}

#endif
//@-leo
