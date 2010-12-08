//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1635: * @thin test_printers.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101208142631.1636: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>

#include "illuminate/test_printers.hpp"
#include "illuminate/test_worker_group.hpp"
#include "illuminate/visitors/indented_output.hpp"
#include "illuminate/visitors/test_future.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1637: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1682: ** struct ColorCodes
ColorCodes::ColorCodes(const string& suite, const string& test, const string& pass, const string& fail, const string& reset)
    : suite(suite)
    , test(test)
    , pass(pass)
    , fail(fail)
    , reset(reset)
{ }

const ColorCodes ColorCodes::plain("","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;32m","\033[1;31m","");
//@+node:gcross.20101208142631.1683: ** Functions
//@+node:gcross.20101208142631.1677: *3* printTestList
void printTestList(const ColorCodes& color_codes,ostream& out) {
    class TestListPrinter : public IndentedOutputVisitor {
    public:
        TestListPrinter(const ColorCodes& color_codes,ostream& out) : IndentedOutputVisitor(out), color_codes(color_codes) { }
    protected:
        virtual void suite(const Suite& suite) { writeIndentedLine(color_codes.suite + suite.name + ":" + color_codes.reset); }
        virtual void test(const Test& test) { writeIndentedLine(color_codes.test + test.name); }
    private:
        const ColorCodes& color_codes;
    } visitor(color_codes,out);
    getRoot().visit(visitor);
}
//@+node:gcross.20101208142631.1680: *3* printTestFutures
void printTestFutures(const TestFutures& futures,const ColorCodes& color_codes,ostream& out) {
    class TestResultPrinter : public IndentedOutputVisitor, public TestFutureVisitor {
    public:
        TestResultPrinter(const TestFutures& futures,const ColorCodes& color_codes,ostream& out)
            : IndentedOutputVisitor(out)
            , TestFutureVisitor(futures)
            , color_codes(color_codes)
        { }
    protected:
        virtual void suite(const Suite& suite) { writeIndentedLine(color_codes.suite + suite.name + ":" + color_codes.reset); }
        virtual void testStarted(const Test& test) { writeIndented(color_codes.test + test.name + "... " + color_codes.reset); }
        virtual void testPassed(const Test& test) { out << color_codes.pass << "PASSED :-)" << color_codes.reset << endl; }
        virtual void testFailed(const Test& test, const vector<string>& failures) { 
            out << color_codes.fail << "FAILED :-(" << color_codes.reset << endl;
            BOOST_FOREACH(const string& m, failures) {
                writeIndentedLine(color_codes.fail + "    * " + m + color_codes.reset);
            }
        }
    private:
        const ColorCodes& color_codes;
    } visitor(futures,color_codes,out);
    getRoot().visit(visitor);
    switch(visitor.number_of_failed_tests) {
        case 0:  out << color_codes.pass << "All tests passed!" << color_codes.reset << endl;  break;
        case 1:  out << color_codes.fail << "1 test failed."    << color_codes.reset << endl;  break;
        default: out << color_codes.fail << visitor.number_of_failed_tests << " tests failed." << color_codes.reset << endl;  break;
    }
}
//@+node:gcross.20101208142631.1684: *3* runTestsAndPrintFutures
void runTestsAndPrintFutures(unsigned int number_of_workers, const ColorCodes& color_codes, ostream& out) {
    TestWorkerGroup workers(number_of_workers);
    printTestFutures(workers.futures,color_codes,out);
}
//@-others

}
//@-leo
