//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1562: * @thin indented_output.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1563: ** << Includes >>
#include <ostream>

#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1564: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1565: ** class IndentedOutputVisitor
//@+node:gcross.20101206161648.1566: *3* (constructors)
IndentedOutputVisitor::IndentedOutputVisitor(ostream& out)
    : indentation(0)
    , out(out)
{ }
//@+node:gcross.20101206161648.1567: *3* enter
void IndentedOutputVisitor::enter(const Suite& suite_) {
    suite(suite_);
    indentation += 4;
}
//@+node:gcross.20101206161648.1568: *3* exit
void IndentedOutputVisitor::exit(const Suite& suite) {
    indentation -= 4;
}
//@+node:gcross.20101206161648.1571: *3* writeIndented
void IndentedOutputVisitor::writeIndented(const string& s) {
    for(int i = 0; i < indentation; ++i) out << ' ';
    out << s;
    out.flush();
}
//@+node:gcross.20101206161648.1573: *3* writeIndentedLine
void IndentedOutputVisitor::writeIndentedLine(const string& s) {
    writeIndented(s);
    out << endl;
    out.flush();
}
//@-others

}
//@-leo
