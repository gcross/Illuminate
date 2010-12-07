//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1548: * @thin indented_output.hpp
//@@language cplusplus

#ifndef VISITORS_INDENTED_OUTPUT_HPP
#define VISITORS_INDENTED_OUTPUT_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1549: ** << Includes >>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1550: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1551: ** class IndentedOutputVisitor
class IndentedOutputVisitor : public Visitor {
protected:
    int indentation;
    ostream& out;
    IndentedOutputVisitor(ostream& out);
    void writeIndented(const string& s);
    void writeIndentedLine(const string& s);
    virtual void enter(const Suite& suite);
    virtual void exit(const Suite& suite);
    virtual void suite(const Suite& suite) = 0;
    virtual void test(Test& test) = 0;
};
//@-others

}

#endif
//@-leo
