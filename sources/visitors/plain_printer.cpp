//@+leo-ver=5-thin
//@+node:gcross.20101205214942.1342: * @thin plain_printer.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205214942.1343: ** << Includes >>
#include <iostream>

#include "illuminate/visitors/plain_printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205214942.1344: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205214942.1350: ** class PlainPrinterVisitor
//@+node:gcross.20101205214942.1351: *3* (constructors)
PlainPrinterVisitor::PlainPrinterVisitor(ostream& out)
    : IndentedOutputVisitor(out)
{ }
//@+node:gcross.20101205214942.1353: *3* suite
void PlainPrinterVisitor::suite(const Suite& suite) {
    writeIndentedLine(suite.name + ":");
}
//@+node:gcross.20101205214942.1356: *3* test
void PlainPrinterVisitor::test(Test& test) {
    writeIndentedLine(test.name);
}
//@+node:gcross.20101205214942.1352: *3* visit
void PlainPrinterVisitor::visit(Suite& suite, ostream& out) {
    PlainPrinterVisitor visitor(out);
    suite.visit(visitor);
}
//@-others

}
//@-leo
