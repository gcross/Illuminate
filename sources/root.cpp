//@+leo-ver=5-thin
//@+node:gcross.20101206104532.1395: * @thin root.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206104532.1396: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206104532.1397: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101206104532.1398: ** class Root
//@+node:gcross.20101206104532.1399: *3* (constructors)
Root::Root() : Suite("Root",NULL) { }
//@+node:gcross.20101206104532.1401: *3* registerTest
int Root::registerTest(Test* test) {
    int test_id = tests.size();
    tests.push_back(test);
    return test_id;
}
//@+node:gcross.20101206104532.1406: ** getRoot
Root& getRoot() {
    static Root root;
    return root;
}
//@-others

}
//@-leo
