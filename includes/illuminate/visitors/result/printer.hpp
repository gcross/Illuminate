//@+leo-ver=5-thin
//@+node:gcross.20110203224841.1950: * @file printer.hpp
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

/*! \file result/printer.hpp
    \brief Illuminate::PrinterResultVisitor class
*/

#ifndef ILLUMINATE_VISITORS_RESULT_PRINTER_HPP
#define ILLUMINATE_VISITORS_RESULT_PRINTER_HPP

//@+<< Includes >>
//@+node:gcross.20110203224841.1951: ** << Includes >>
#include <ostream>

#include "../../color_codes.hpp"
#include "../indented_output.hpp"
#include "../result.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110203224841.1953: ** class PrinterResultVisitor
//! Result visitor that prints all tests and their test results
/*!
\note Users of this class need to subclass it and supply an implementation of ResultVisitor::test that calls the appropriate \c test___() methods of this class;  alternatively one can mix in either FutureResultVisitor or RunnerResultVisitor.
*/
class PrinterResultVisitor : public IndentedOutputVisitor, public virtual ResultVisitor {
public:
    //! Constructor
    PrinterResultVisitor(
        //! processor that should be used to process tests */
        TestResultFetcher fetchTestResult,
        //! the color code escape sequences to use when printing the test results
        const ColorCodes& color_codes,
        //! the output device to which the test tree should be printed
        std::ostream& out
    );
protected:
    virtual void suite(Suite const& suite);
    virtual void testSkipped(Test const& test);
    virtual void testStarted(Test const& test);
    virtual void testPassed(Test const& test);
    virtual void testFailed(Test const& test, std::vector<std::string> const& failures);
private:
    ColorCodes const& color_codes;
};
//@-others

}

#endif
//@-leo
