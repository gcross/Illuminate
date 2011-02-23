//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1562: * @thin indented_output.cpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110222175650.1654: ** << License >>
//@+at
// ISC License (http://www.opensource.org/licenses/isc-license)
// 
// Copyright (c) 2011, Gregory Crosswhite <gcrosswhite@gmail.com>
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//@@c
//@-<< License >>

//@+<< Includes >>
//@+node:gcross.20101206161648.1563: ** << Includes >>
#include <ostream>

#include "illuminate/visitors/indented_output.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1564: ** << Usings >>
using std::endl;
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
