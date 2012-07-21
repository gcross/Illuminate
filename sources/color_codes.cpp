// Includes {{{
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>

#include "illuminate/color_codes.hpp"
#include "illuminate/test_tree.hpp"
// }}}

// Usings {{{
using boost::any;
using boost::equals;
using boost::format;
using boost::program_options::invalid_option_value;
namespace validators = boost::program_options::validators;
using boost::to_lower;

using std::endl;
using std::string;
using std::vector;
// }}}

namespace Illuminate {

// struct ColorCodes {{{
ColorCodes const ColorCodes::plain("","","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;35m","\033[1;32m","\033[1;31m","\033[0;0m");

ColorCodes::ColorCodes(string const& suite, string const& test, string const& skip, string const& pass, string const& fail, string const& reset) // {{{
    : suite(suite)
    , test(test)
    , skip(skip)
    , pass(pass)
    , fail(fail)
    , reset(reset)
{ } // }}}
format ColorCodes::failed() const { // {{{
    return format("%1%FAILED :-(%2%") % fail % reset;
} // }}}
format ColorCodes::failure(string const& m) const { // {{{
    return format("    %1%* %2%%3%") % fail % m % reset;
} // }}}
format ColorCodes::passed() const { // {{{
    return format("%1%PASSED :-)%2%") % pass % reset;
} // }}}
format ColorCodes::numberOfFailedTests(unsigned int const number_of_failed_tests) const { // {{{
    switch(number_of_failed_tests) {
        case 0:  return format("%1%%2%%3%") % pass % "All tests passed!" % reset;
        case 1:  return format("%1%%2%%3%") % fail % "1 test failed."    % reset;
        default: return format("%1%%2%%3%%4%") % fail % number_of_failed_tests % " tests failed." % reset;
    }
} // }}}
format ColorCodes::suiteEntered(Suite const& s) const { // {{{
    return format(suite + s.name + ":" + reset);
} // }}}
format ColorCodes::testName(Test const& t) const { // {{{
    return format("%1%%2% [#%3%]%4%")
        % test
        % t.name
        % t.id
        % reset
    ;
} // }}}
format ColorCodes::testPath(Test const& t) const { // {{{
    return format("%1%%2% [#%3%]%4%")
        % test
        % t.constructPath()
        % t.id
        % reset
    ;
} // }}}
format ColorCodes::testNameAndSkipped(Test const& t) const { // {{{
    return format("%1%%2% [#%3%] %4%%5%")
        % test
        % t.name
        % t.id
        % (t.skipped ? " (skipped)" : "")
        % reset
    ;
} // }}}
format ColorCodes::testSkipped() const { // {{{
    return format("%1%... %2%(skipped)%3%") % test % skip % reset;
} // }}}
format ColorCodes::testStarted() const { // {{{
    return format("%1%... %2%") % test % reset;
} // }}}
// }}}

void validate(any& v
             ,vector<std::string> const& values
             ,Coloring* target_type
             ,int
             )
{ // {{{
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
} // }}}

}
