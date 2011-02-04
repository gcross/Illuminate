//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1536: * @thin color_codes.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20110203233241.1537: ** << Includes >>
#include "illuminate/color_codes.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1624: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1540: ** struct ColorCodes
ColorCodes::ColorCodes(const string& suite, const string& test, const string& pass, const string& fail, const string& reset)
    : suite(suite)
    , test(test)
    , pass(pass)
    , fail(fail)
    , reset(reset)
{ }

const ColorCodes ColorCodes::plain("","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;32m","\033[1;31m","");
//@-others

}
//@-leo
