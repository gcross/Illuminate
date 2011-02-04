//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1546: * @thin printer.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_PRINTER_HPP
#define ILLUMINATE_VISITORS_PRINTER_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1547: ** << Includes >>
#include "illuminate/color_codes.hpp"
#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1548: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1549: ** class PrinterVisitor
class PrinterVisitor : public IndentedOutputVisitor {
public:
    PrinterVisitor(const ColorCodes& color_codes,ostream& out);
protected:
    virtual void suite(const Suite& suite);
    virtual void test(const Test& test);
private:
    const ColorCodes& color_codes;
};
//@-others

}

#endif
//@-leo
