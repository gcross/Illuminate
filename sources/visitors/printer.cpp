//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1588: * @thin printer.cpp
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
//@+node:gcross.20110203233241.1589: ** << Includes >>
#include <boost/foreach.hpp>

#include "illuminate/visitors/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1590: ** << Usings >>
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
void PrinterVisitor::test(const Test& test) { writeIndentedLine(color_codes.test + test.name + (test.skipped ? " (skipped)" : "") + color_codes.reset); }
//@-others

}
//@-leo
