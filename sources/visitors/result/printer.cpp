//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1570: * @file printer.cpp
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
//@+node:gcross.20110203224841.1961: ** << Includes >>
#include <boost/foreach.hpp>

#include "illuminate/visitors/result/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203224841.1962: ** << Usings >>
using boost::format;

using std::endl;
using std::ostream;
using std::string;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203224841.1963: ** class PrinterResultVisitor
//@+node:gcross.20110203224841.1964: *3* (constructors)
PrinterResultVisitor::PrinterResultVisitor(
    TestResultFetcher fetchTestResult
  , ColorCodes const& color_codes
  , ostream& out
)
  : ResultVisitor(fetchTestResult)
  , IndentedOutputVisitor(out)
  , color_codes(color_codes)
{ }
//@+node:gcross.20110203224841.1965: *3* suite
void PrinterResultVisitor::suite(Suite const& suite) {
    writeIndentedLine(color_codes.suiteEntered(suite));
}
//@+node:gcross.20110222194651.1593: *3* testSkipped
void PrinterResultVisitor::testSkipped(Test const& test) {
    writeIndentedLine(format("%1%%2%") % color_codes.testName(test) % color_codes.testSkipped());
}
//@+node:gcross.20110203224841.1966: *3* testStarted
void PrinterResultVisitor::testStarted(Test const& test) {
    writeIndented(format("%1%%2%") % color_codes.testName(test) % color_codes.testStarted());
}
//@+node:gcross.20110203224841.1967: *3* testPassed
void PrinterResultVisitor::testPassed(Test const& test) {
    out << color_codes.passed() << endl; out.flush();
}
//@+node:gcross.20110203224841.1968: *3* testFailed
void PrinterResultVisitor::testFailed(Test const& test, vector<string> const& failures) {
    out << color_codes.failed() << endl;
    BOOST_FOREACH(const string& m, failures) {
        writeIndentedLine(color_codes.failure(m));
    }
}
//@-others

}
//@-leo
