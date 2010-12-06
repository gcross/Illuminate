//@+leo-ver=5-thin
//@+node:gcross.20101205214942.1345: * @thin plain_printer.hpp
//@@language cplusplus

#ifndef VISITORS_PLAIN_PRINTER_HPP
#define VISITORS_PLAIN_PRINTER_HPP

//@+<< Includes >>
//@+node:gcross.20101205214942.1346: ** << Includes >>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205214942.1347: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205214942.1348: ** class PlainPrinterVisitor
class PlainPrinterVisitor : public Visitor {
    int indentation;
    ostream& out;
    PlainPrinterVisitor(ostream& out);
    void writeIndentedLine(const string& s);
public:
    virtual void enter(const Suite& suite);
    virtual void exit(const Suite& suite);
    virtual void test(Test& test);
    static void visit(Suite& suite, ostream& out=cout);
};
//@-others

}

#endif
//@-leo
