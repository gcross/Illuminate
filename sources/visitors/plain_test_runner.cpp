//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1590: * @thin plain_test_runner.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1591: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>

#include "illuminate/visitors/plain_test_runner.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1592: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1593: ** class PlainTestRunnerVisitor
//@+node:gcross.20101206161648.1594: *3* (constructors)
PlainTestRunnerVisitor::PlainTestRunnerVisitor(ostream& out)
    : IndentedOutputVisitor(out)
    , number_of_failed_tests(0)
{ }
//@+node:gcross.20101206161648.1595: *3* suite
void PlainTestRunnerVisitor::suite(const Suite& suite) {
    writeIndentedLine(suite.name + ":");
}
//@+node:gcross.20101206161648.1596: *3* test
void PlainTestRunnerVisitor::test(Test& test) {
    writeIndented(test.name + "... ");
    auto_ptr<vector<string> > failures = test.run();
    if(failures->size() == 0) {
        out << "PASSED  :-D" << endl;
    } else {
        out << "FAILED  :-(" << endl;
        BOOST_FOREACH(const string& m, *failures) {
            writeIndentedLine("    * " + m);
        }
        ++number_of_failed_tests;
    }
}
//@+node:gcross.20101206161648.1597: *3* runTests
void PlainTestRunnerVisitor::runTests(ostream& out) {
    PlainTestRunnerVisitor visitor(out);
    getRoot().visit(visitor);
    switch(visitor.number_of_failed_tests) {
        case 0: out << "All tests passed!" << endl;  break;
        case 1: out << "1 test failed" << endl;  break;
        default: out << visitor.number_of_failed_tests << " tests failed" << endl;  break;
    }
}
//@-others

}
//@-leo
