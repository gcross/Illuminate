//@+leo-ver=5-thin
//@+node:gcross.20110203224841.1950: * @thin printer.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_RESULT_PRINTER_HPP
#define ILLUMINATE_VISITORS_RESULT_PRINTER_HPP

//@+<< Includes >>
//@+node:gcross.20110203224841.1951: ** << Includes >>
#include <ostream>

#include "illuminate/color_codes.hpp"
#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203224841.1952: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203224841.1953: ** class PrinterResultVisitor
class PrinterResultVisitor : public IndentedOutputVisitor, public virtual ResultVisitor {
public:
    PrinterResultVisitor(const ColorCodes& color_codes,ostream& out);
protected:
    virtual void suite(const Suite& suite);
    virtual void testStarted(const Test& test);
    virtual void testPassed(const Test& test);
    virtual void testFailed(const Test& test, const vector<string>& failures);
private:
    const ColorCodes& color_codes;
};
//@-others

}

#endif
//@-leo
