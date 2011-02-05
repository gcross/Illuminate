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

const ColorCodes ColorCodes::plain("","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;32m","\033[1;31m","\033[0;0m");
//@+node:gcross.20110204202041.1567: ** function validate
void validate(any& v,
              const vector<std::string>& values,
              Coloring* target_type, int)
{
    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);

    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    string s = validators::get_single_string(values);
    to_lower(s);

    static string const plain("plain"), ansi("ansi");
    if(equals(s,plain)) {
        v = any(PLAIN_COLORING);
    } else if(equals(s,ansi)) {
        v = any(ANSI_COLORING);
    } else {
        throw invalid_option_value(s);
    }
}
//@-others

}
//@-leo
