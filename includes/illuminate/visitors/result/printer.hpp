/*! \file result/printer.hpp
    \brief Illuminate::PrinterResultVisitor class
*/

#ifndef ILLUMINATE_VISITORS_RESULT_PRINTER_HPP
#define ILLUMINATE_VISITORS_RESULT_PRINTER_HPP

// Includes {{{
#include <ostream>

#include "../../color_codes.hpp"
#include "../indented_output.hpp"
#include "../result.hpp"
// }}}

namespace Illuminate {

//! Result visitor that prints all tests and their test results
/*!
\note Users of this class need to subclass it and supply an implementation of ResultVisitor::test that calls the appropriate \c test___() methods of this class;  alternatively one can mix in either FutureResultVisitor or RunnerResultVisitor.
*/
class PrinterResultVisitor : public IndentedOutputVisitor, public virtual ResultVisitor { // {{{
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
}; // }}}

}

#endif
