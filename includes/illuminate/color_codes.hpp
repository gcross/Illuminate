//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1528: * @thin color_codes.hpp
//@@language cplusplus

#ifndef ILLUMINATE_COLOR_CODES_HPP
#define ILLUMINATE_COLOR_CODES_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1529: ** << Includes >>
#include <string>
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1530: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1531: ** struct ColorCodes
struct ColorCodes {
    ColorCodes(const string& suite, const string& test, const string& pass, const string& fail, const string& reset);
    string suite, test, pass, fail, reset;
    static const ColorCodes plain, ANSI;
};
//@-others

}

#endif
//@-leo
