//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1528: * @thin color_codes.hpp
//@@language cplusplus

#ifndef ILLUMINATE_COLOR_CODES_HPP
#define ILLUMINATE_COLOR_CODES_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1529: ** << Includes >>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/any.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <vector>
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1530: ** << Usings >>
using namespace boost;
using namespace boost::program_options;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1531: ** struct ColorCodes
struct ColorCodes {
    ColorCodes(const string& suite, const string& test, const string& pass, const string& fail, const string& reset);
    string suite, test, pass, fail, reset;
    static const ColorCodes plain, ANSI;
};
//@+node:gcross.20110204202041.1563: ** enum Coloring
enum Coloring { ANSI_COLORING, PLAIN_COLORING };
//@+node:gcross.20110204202041.1565: ** function validate
void validate(
      any& v
    , const vector<std::string>& values
    , Coloring* target_type
    , int
);
//@-others

}

#endif
//@-leo
