//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1578: * @thin plain_test_runner.hpp
//@@language cplusplus

#ifndef VISITORS_PLAIN_TEST_RUNNER_HPP
#define VISITORS_PLAIN_TEST_RUNNER_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1579: ** << Includes >>
#include <iostream>

#include "illuminate.hpp"
#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1580: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1581: ** class PlainTestRunnerVisitor
class PlainTestRunnerVisitor : public IndentedOutputVisitor {
protected:
    int number_of_failed_tests;
    PlainTestRunnerVisitor(ostream& out);
    virtual void suite(const Suite& test);
    virtual void test(Test& test);
public:
    static void visit(Suite& suite, ostream& out=cout);
};
//@-others

}

#endif
//@-leo
