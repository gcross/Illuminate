//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1548: * @thin indented_output.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP
#define ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1549: ** << Includes >>
#include <iostream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1550: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1551: ** class IndentedOutputVisitor
class IndentedOutputVisitor : public virtual Visitor {
protected:
    int indentation;
    ostream& out;
    IndentedOutputVisitor(ostream& out);
    void writeIndented(const string& s);
    void writeIndentedLine(const string& s);
    virtual void enter(const Suite& suite);
    virtual void exit(const Suite& suite);
    virtual void suite(const Suite& suite) = 0;
};
//@-others

}

#endif
//@-leo
