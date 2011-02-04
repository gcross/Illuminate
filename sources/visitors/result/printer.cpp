//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1570: * @thin printer.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20110203224841.1961: ** << Includes >>
#include <boost/foreach.hpp>

#include "illuminate/visitors/result/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203224841.1962: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203224841.1963: ** class PrinterResultVisitor
//@+node:gcross.20110203224841.1964: *3* (constructors)
PrinterResultVisitor::PrinterResultVisitor(const ColorCodes& color_codes,ostream& out)
    : IndentedOutputVisitor(out)
    , color_codes(color_codes)
{ }
//@+node:gcross.20110203224841.1965: *3* suite
void PrinterResultVisitor::suite(const Suite& suite) {
    writeIndentedLine(color_codes.suite + suite.name + ":" + color_codes.reset);
}
//@+node:gcross.20110203224841.1966: *3* testStarted
void PrinterResultVisitor::testStarted(const Test& test) {
    writeIndented(color_codes.test + test.name + "... " + color_codes.reset);
}
//@+node:gcross.20110203224841.1967: *3* testPassed
void PrinterResultVisitor::testPassed(const Test& test) {
    out << color_codes.pass << "PASSED :-)" << color_codes.reset << endl;  out.flush();
}
//@+node:gcross.20110203224841.1968: *3* testFailed
void PrinterResultVisitor::testFailed(const Test& test, const vector<string>& failures) { 
    out << color_codes.fail << "FAILED :-(" << color_codes.reset << endl;
    BOOST_FOREACH(const string& m, failures) {
        writeIndentedLine(color_codes.fail + "    * " + m + color_codes.reset);
    }
}
//@-others

}
//@-leo
