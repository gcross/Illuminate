//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1588: * @thin printer.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20110203233241.1589: ** << Includes >>
#include <boost/foreach.hpp>

#include "illuminate/visitors/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1590: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1591: ** class PrinterVisitor
//@+node:gcross.20110203233241.1592: *3* (constructors)
PrinterVisitor::PrinterVisitor(const ColorCodes& color_codes,ostream& out)
    : IndentedOutputVisitor(out)
    , color_codes(color_codes)
{ }
//@+node:gcross.20110203233241.1593: *3* suite
void PrinterVisitor::suite(const Suite& suite) {
    writeIndentedLine(color_codes.suite + suite.name + ":" + color_codes.reset);
}
//@+node:gcross.20110203233241.1597: *3* test
void PrinterVisitor::test(const Test& test) { writeIndentedLine(color_codes.test + test.name + color_codes.reset); }
//@-others

}
//@-leo
