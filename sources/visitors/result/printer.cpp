// Includes {{{
#include <boost/foreach.hpp>

#include "illuminate/visitors/result/printer.hpp"
// }}}

// Usings {{{
using boost::format;

using std::endl;
using std::ostream;
using std::string;
using std::vector;
// }}}

namespace Illuminate {

// class PrinterResultVisitor {{{
PrinterResultVisitor::PrinterResultVisitor( // {{{
    TestResultFetcher fetchTestResult
  , ColorCodes const& color_codes
  , ostream& out
)
  : ResultVisitor(fetchTestResult)
  , IndentedOutputVisitor(out)
  , color_codes(color_codes)
{ } // }}}
void PrinterResultVisitor::suite(Suite const& suite) { // {{{
    writeIndentedLine(color_codes.suiteEntered(suite));
} // }}}
void PrinterResultVisitor::testSkipped(Test const& test) { // {{{
    writeIndentedLine(format("%1%%2%") % color_codes.testName(test) % color_codes.testSkipped());
} // }}}
void PrinterResultVisitor::testStarted(Test const& test) { // {{{
    writeIndented(format("%1%%2%") % color_codes.testName(test) % color_codes.testStarted());
} // }}}
void PrinterResultVisitor::testPassed(Test const& test) { // {{{
    out << color_codes.passed() << endl; out.flush();
} // }}}
void PrinterResultVisitor::testFailed(Test const& test, vector<string> const& failures) { // {{{
    out << color_codes.failed() << endl;
    BOOST_FOREACH(const string& m, failures) {
        writeIndentedLine(color_codes.failure(m));
    }
} // }}}
// }}}

}
