//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1635: * @thin runners.cpp
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
//@+node:gcross.20101208142631.1636: ** << Includes >>
#include <ostream>

#include "illuminate/runners.hpp"
#include "illuminate/test_worker_group.hpp"
#include "illuminate/visitors/result/future.hpp"
#include "illuminate/visitors/result/printer.hpp"
#include "illuminate/visitors/result/runner.hpp"
#include "illuminate/visitors/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1637: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1683: ** Functions
//@+node:gcross.20101208142631.1677: *3* printTestList
void printTestList(const ColorCodes& color_codes,ostream& out) {
    PrinterVisitor visitor(color_codes,out);
    getRoot().visit(visitor);
}
//@+node:gcross.20101208142631.1680: *3* printTestFutures
void printTestFutures(const TestFutures& futures,const ColorCodes& color_codes,ostream& out) {
    class TestVisitor : public FutureResultVisitor, public PrinterResultVisitor {
    public:
        TestVisitor(const TestFutures& futures,const ColorCodes& color_codes,ostream& out)
            : FutureResultVisitor(futures)
            , PrinterResultVisitor(color_codes,out)
        { }
    } visitor(futures,color_codes,out);
    getRoot().visit(visitor);
    switch(visitor.number_of_failed_tests) {
        case 0:  out << color_codes.pass << "All tests passed!" << color_codes.reset << endl;  break;
        case 1:  out << color_codes.fail << "1 test failed."    << color_codes.reset << endl;  break;
        default: out << color_codes.fail << visitor.number_of_failed_tests << " tests failed." << color_codes.reset << endl;  break;
    }
}
//@+node:gcross.20110204143810.1552: *3* runTestsAndPrintResults
void runTestsAndPrintResults(const ColorCodes& color_codes, ostream& out) {
    class TestVisitor : public RunnerResultVisitor, public PrinterResultVisitor {
    public:
        TestVisitor(const ColorCodes& color_codes,ostream& out)
            : PrinterResultVisitor(color_codes,out)
        { }
    } visitor(color_codes,out);
    getRoot().visit(visitor);
    switch(visitor.number_of_failed_tests) {
        case 0:  out << color_codes.pass << "All tests passed!" << color_codes.reset << endl;  break;
        case 1:  out << color_codes.fail << "1 test failed."    << color_codes.reset << endl;  break;
        default: out << color_codes.fail << visitor.number_of_failed_tests << " tests failed." << color_codes.reset << endl;  break;
    }
}
//@+node:gcross.20101208142631.1684: *3* runTestsInThreadsAndPrintResults
void runTestsInThreadsAndPrintResults(optional<unsigned int> const requested_number_of_workers, const ColorCodes& color_codes, ostream& out) {
    unsigned int const number_of_workers = 
        requested_number_of_workers
            ? *requested_number_of_workers
            : max(thread::hardware_concurrency(),(unsigned int)1)
            ;
    TestWorkerGroup workers(number_of_workers);
    printTestFutures(workers.futures,color_codes,out);
}
//@-others

}
//@-leo
