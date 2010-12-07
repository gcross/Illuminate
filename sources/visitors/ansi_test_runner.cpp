//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1745: * @thin ansi_test_runner.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1746: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>

#include "illuminate/visitors/ansi_test_runner.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1747: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1748: ** class ANSITestRunnerVisitor
//@+node:gcross.20101206161648.1749: *3* (constructors)
ANSITestRunnerVisitor::ANSITestRunnerVisitor(ostream& out)
    : IndentedOutputVisitor(out)
    , number_of_failed_tests(0)
{ }
//@+node:gcross.20101206161648.1750: *3* suite
void ANSITestRunnerVisitor::suite(const Suite& suite) {
    writeIndentedLine("\033[43m" + suite.name + ":\033[0m");
}
//@+node:gcross.20101206161648.1751: *3* test
void ANSITestRunnerVisitor::test(Test& test) {
    writeIndented("\033[1;33m" + test.name + "... \033[0m");
    auto_ptr<vector<string> > failures = test.run();
    if(failures->size() == 0) {
        out << "\033[1;32m PASSED :-) \033[0m" << endl;
    } else {
        out << "\033[1;31m FAIL :-( \033[0m" << endl;
        BOOST_FOREACH(const string& m, *failures) {
            writeIndentedLine("\033[1;31m    * " + m + "\033[0m");
        }
        ++number_of_failed_tests;
    }
}
//@+node:gcross.20101206161648.1752: *3* runTests
void ANSITestRunnerVisitor::runTests(ostream& out) {
    ANSITestRunnerVisitor visitor(out);
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
