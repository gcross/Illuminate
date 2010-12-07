//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1606: * @thin main.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1607: ** << Includes >>
#include "illuminate.hpp"
#include "illuminate/visitors/ansi_test_runner.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20101206161648.1609: ** main
int main() {
    Illuminate::ANSITestRunnerVisitor::runTests();
    return 0;
}
//@-others
//@-leo
