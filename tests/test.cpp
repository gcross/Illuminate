//@+leo-ver=5-thin
//@+node:gcross.20101205214942.1329: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205214942.1340: ** << Includes >>
#include "illuminate.hpp"
#include "visitors/plain_printer.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20101205214942.1927: ** Tests
testSuite(Suite_1) {
    testSuite(subSuite_A) { static Illuminate::Suite parent = getParentSuite(); }
}
testSuite(Suite_2) {
    testSuite(subSuite) { static Illuminate::Suite parent = getParentSuite(); }
}
//@+node:gcross.20101205214942.1926: ** main
int main() {
    Illuminate::PlainPrinterVisitor::visit(Illuminate::getRoot());
    return 0;
}
//@-others
//@-leo
