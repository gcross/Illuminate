//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1848: * @thin test_queuer.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1849: ** << Includes >>
#include <iostream>

#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1850: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1851: ** class TestQueuer
//@+node:gcross.20101206161648.1852: *3* (constructors)
TestQueuer::TestQueuer(TestQueue& queue, TestResults& results)
    : queue(queue)
    , results(results)
{ }
//@+node:gcross.20101206161648.1853: *3* enter
void TestQueuer::enter(const Suite& suite_) { }
//@+node:gcross.20101206161648.1854: *3* exit
void TestQueuer::exit(const Suite& suite) { }
//@+node:gcross.20101206161648.1860: *3* test
void TestQueuer::test(Test& test) {
    TestTask task(
}
//@-others

}
//@-leo
