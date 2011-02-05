//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1623: * @thin runners.hpp
//@@language cplusplus

#ifndef ILLUMINATE_RUNNERS_HPP
#define ILLUMINATE_RUNNERS_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1624: ** << Includes >>
#include <algorithm>
#include <iostream>

#include "illuminate/core.hpp"
#include "illuminate/color_codes.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1625: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1667: ** Functions
void printTestList(const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
void printTestFutures(const TestFutures& futures, const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
void runTestsAndPrintResults(const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
void runTestsInThreadsAndPrintResults(unsigned int number_of_workers=max(thread::hardware_concurrency(),(unsigned int)1), const ColorCodes& color_codes=ColorCodes::ANSI, ostream& out=cout);
//@-others

}

#endif
//@-leo
