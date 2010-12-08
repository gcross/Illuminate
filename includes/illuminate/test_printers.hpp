//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1623: * @thin test_printers.hpp
//@@language cplusplus

#ifndef VISITORS_ANSI_TEST_PRINTERS_HPP
#define VISITORS_ANSI_TEST_PRINTERS_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1624: ** << Includes >>
#include <algorithm>
#include <iostream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1625: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1681: ** struct ColorCodes
struct ColorCodes {
    ColorCodes(const string& suite, const string& test, const string& pass, const string& fail, const string& reset);
    string suite, test, pass, fail, reset;
    static const ColorCodes plain, ANSI;
};
//@+node:gcross.20101208142631.1667: ** Functions
void printTestList(const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
void printTestFutures(const TestFutures& futures, const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
void runTestsAndPrintFutures(unsigned int number_of_workers=max(thread::hardware_concurrency(),(unsigned int)1), const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
//@-others

}

#endif
//@-leo
