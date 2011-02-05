//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1635: * @thin runners.cpp
//@@language cplusplus

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
using namespace std;
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
void runTestsInThreadsAndPrintResults(unsigned int number_of_workers, const ColorCodes& color_codes, ostream& out) {
    TestWorkerGroup workers(number_of_workers);
    printTestFutures(workers.futures,color_codes,out);
}
//@-others

}
//@-leo
