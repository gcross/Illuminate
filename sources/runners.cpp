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
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/lambda/lambda.hpp>
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
namespace lambda = boost::lambda;
using boost::optional;
using boost::promise;
using boost::shared_ptr;
using boost::unique_future;

using std::endl;
using std::make_pair;
using std::string;
using std::ostream;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1683: ** Functions
//@+node:gcross.20101208142631.1486: *3* enqueueAllTests
void enqueueAllTests(TestQueue const& queue, TestFutures const& futures, Suite const& suite) {
    struct : public Visitor {
        TestQueue queue;
        TestFutures futures;
        virtual void enter(Suite const& _) {}
        virtual void exit(Suite const& _) {}
        virtual void test(Test const& test) {
            if(!test.skipped) { enqueueTest(queue,futures,test.id); }
        }
    } queuer;
    queuer.queue = queue;
    queuer.futures = futures;
    suite.visit(queuer);
}
//@+node:gcross.20110813230314.1515: *3* enqueueSelectedTests
void enqueueSelectedTests(TestQueue const& queue, TestFutures const& futures, vector<unsigned int> const& test_ids) {
    BOOST_FOREACH(unsigned int const test_id, test_ids) {
        if((*futures).find(test_id) == futures->end()) {
            enqueueTest(queue,futures,test_id);
        }
    }
}
//@+node:gcross.20110813230314.1516: *3* enqueueTest
void enqueueTest(TestQueue const& queue, TestFutures const& futures, unsigned int test_id) {
    TestTask task(make_pair(test_id,new promise<TestResult>()));
    TestFuture future(new unique_future<TestResult>);
    (*future) = task.second->get_future();
    (*futures)[test_id] = future;
    queue->push(task);
}
//@+node:gcross.20110204143810.1552: *3* printAllTestResults
void printAllTestResults(
    ColorCodes const& color_codes,
    ostream& out,
    TestResultFetcher fetchResult
) {
    PrinterResultVisitor visitor(fetchResult,color_codes,out);
    getRoot().visit(visitor);
    printTestFailureCount(visitor.number_of_failed_tests,color_codes,out);
}
//@+node:gcross.20110809112154.2053: *3* printSelectedTestResults
void printSelectedTestResults(
    vector<unsigned int> const& test_ids,
    ColorCodes const& color_codes,
    ostream& out,
    TestResultFetcher fetchResult
) {
    Root const& root = getRoot();
    unsigned int number_of_failed_tests = 0;
    BOOST_FOREACH(unsigned int const test_id, test_ids) {
        Test const& test = root.lookupTest(test_id);
        out << color_codes.testPath(test) << color_codes.testStarted();
        TestResult result = fetchResult(test.id);
        if(result->size() == 0) {
            out << color_codes.passed() << endl;
        } else {
            ++number_of_failed_tests;
            out << color_codes.failed() << endl;
            BOOST_FOREACH(const string& m, *result) {
                out << color_codes.failure(m) << endl;
            }
        }
    }
    printTestFailureCount(number_of_failed_tests);
}
//@+node:gcross.20110601150226.2636: *3* printTestFailureCount
void printTestFailureCount(
    unsigned int number_of_failed_tests,
    ColorCodes const& color_codes,
    ostream& out
) {
    out << endl << color_codes.numberOfFailedTests(number_of_failed_tests) << endl;
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
            writeIndentedLine(color_codes.testNameAndSkipped(test));
        }
    } visitor(color_codes,out);
    getRoot().visit(visitor);
}
//@+node:gcross.20101208142631.1684: *3* runAllTestsUsingWorkersAndPrintResults
void runAllTestsUsingWorkersAndPrintResults(
    unsigned int number_of_workers,
    ColorCodes const& color_codes,
    ostream& out,
    TestResultFetcher fetchResult
) {
    TestWorkerGroup workers(number_of_workers,fetchResult);
    printAllTestResults(color_codes,out,FutureTestResultFetcher(workers.futures));
}
//@+node:gcross.20110813230314.1520: *3* runSelectedTestsUsingWorkersAndPrintResults
void runSelectedTestsUsingWorkersAndPrintResults(
    vector<unsigned int> const& test_ids,
    unsigned int number_of_workers,
    ColorCodes const& color_codes,
    ostream& out,
    TestResultFetcher fetchResult
) {
    TestWorkerGroup workers(number_of_workers,fetchResult,test_ids);
    printSelectedTestResults(test_ids,color_codes,out,FutureTestResultFetcher(workers.futures));
}
//@-others

}
//@-leo
