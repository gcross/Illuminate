// Includes {{{
#include <ostream>

#include "illuminate/visitors/indented_output.hpp"
// }}}

// Usings {{{
using boost::format;

using std::endl;
using std::ostream;
using std::string;
// }}}

namespace Illuminate {

// class IndentedOutputVisitor {{{
IndentedOutputVisitor::IndentedOutputVisitor(ostream& out) // {{{
    : indentation(0)
    , out(out)
{ } // }}}
void IndentedOutputVisitor::enter(Suite const& suite_) { // {{{
    suite(suite_);
    indentation += 4;
} // }}}
void IndentedOutputVisitor::exit(Suite const& suite) { // {{{
    indentation -= 4;
} // }}}
void IndentedOutputVisitor::writeIndentation() { // {{{
    for(int i = 0; i < indentation; ++i) out << ' ';
} // }}}
// void IndentedOutputVisitor::writeIndented(...) {{{
void IndentedOutputVisitor::writeIndented(format const& s) {
    writeIndentation();
    out << s;
    out.flush();
}

void IndentedOutputVisitor::writeIndented(string const& s) {
    writeIndentation();
    out << s;
    out.flush();
}
// }}}
// void IndentedOutputVisitor::writeIndentedLine(...) {{{
void IndentedOutputVisitor::writeIndentedLine(format const& s) {
    writeIndented(s);
    out << endl;
    out.flush();
}

void IndentedOutputVisitor::writeIndentedLine(string const& s) {
    writeIndented(s);
    out << endl;
    out.flush();
}
// }}}
// }}}

}
