//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1635: * @file runners.cpp
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
#include <boost/format.hpp>
#include <ostream>

#include "illuminate/runners.hpp"
#include "illuminate/test_result_fetchers/future.hpp"
#include "illuminate/test_worker_group.hpp"
#include "illuminate/visitors/indented_output.hpp"
#include "illuminate/visitors/result/printer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1637: ** << Usings >>
using boost::format;
using boost::optional;
using boost::promise;
using boost::thread;
using boost::unique_future;

using std::endl;
using std::make_pair;
using std::max;
using std::ostream;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1683: ** Functions
//@+node:gcross.20101208142631.1486: *3* enqueueTests
void enqueueTests(TestQueue const& queue, TestFutures const& futures, Suite const& suite) {
    struct : public Visitor {
        TestQueue queue;
        TestFutures futures;
        virtual void enter(Suite const& _) {}
        virtual void exit(Suite const& _) {}
        virtual void test(Test const& test) {
            if(!test.skipped) {
                TestTask task(make_pair(test.id,new promise<TestResult>()));
                TestFuture future(new unique_future<TestResult>);
                (*future) = task.second->get_future();
                (*futures)[test.id] = future;
                queue->push(task);
            }
        }
    } queuer;
    queuer.queue = queue;
    queuer.futures = futures;
    suite.visit(queuer);
}
//@+node:gcross.20110601150226.2636: *3* printTestFailureCount
void printTestFailureCount(
    unsigned int number_of_failed_tests,
    ColorCodes const& color_codes,
    ostream& out
) {
    out << endl;
    switch(number_of_failed_tests) {
        case 0:  out << color_codes.pass << "All tests passed!" << color_codes.reset << endl;  break;
        case 1:  out << color_codes.fail << "1 test failed."    << color_codes.reset << endl;  break;
        default: out << color_codes.fail << number_of_failed_tests << " tests failed." << color_codes.reset << endl;  break;
    }
}
//@+node:gcross.20101208142631.1680: *3* printTestFutures
void printTestFutures(TestFutures const& futures,ColorCodes const& color_codes,ostream& out) {
    PrinterResultVisitor visitor(FutureTestResultFetcher(futures),color_codes,out);
    getRoot().visit(visitor);
    printTestFailureCount(visitor.number_of_failed_tests,color_codes,out);
}
//@+node:gcross.20101208142631.1677: *3* printTestTree
void printTestTree(ColorCodes const& color_codes,ostream& out) {
    struct PrinterVisitor : public IndentedOutputVisitor {
        ColorCodes const& color_codes;
        PrinterVisitor(ColorCodes const& color_codes,std::ostream& out)
            : IndentedOutputVisitor(out)
            , color_codes(color_codes)
        { }
        virtual void suite(Suite const& suite) {
            writeIndentedLine(color_codes.suite + suite.name + ":" + color_codes.reset);
        }
        virtual void test(Test const& test) {
            writeIndentedLine(
                (format("%1%%2% [#%3%] %4%%5%")
                    % color_codes.test
                    % test.name
                    % test.id
                    % (test.skipped ? " (skipped)" : "")
                    % color_codes.reset
                ).str()
            );
        }
    } visitor(color_codes,out);
    getRoot().visit(visitor);
}
//@+node:gcross.20110204143810.1552: *3* runTestsAndPrintResults
void runTestsAndPrintResults(ColorCodes const& color_codes, ostream& out) {
    PrinterResultVisitor visitor(Test::run,color_codes,out);
    getRoot().visit(visitor);
    printTestFailureCount(visitor.number_of_failed_tests,color_codes,out);
}
//@+node:gcross.20101208142631.1684: *3* runTestsInThreadsAndPrintResults
void runTestsInThreadsAndPrintResults(optional<unsigned int> const requested_number_of_workers, ColorCodes const& color_codes, ostream& out) {
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
