//@+leo-ver=5-thin
//@+node:gcross.20110203224841.1950: * @thin printer.hpp
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
//@-<< Usings >>

//@+others
//@+node:gcross.20110203224841.1953: ** class PrinterResultVisitor
class PrinterResultVisitor : public IndentedOutputVisitor, public virtual ResultVisitor {
public:
    PrinterResultVisitor(const ColorCodes& color_codes,ostream& out);
protected:
    virtual void suite(const Suite& suite);
    virtual void testSkipped(const Test& test);
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
