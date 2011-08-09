//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1536: * @file color_codes.cpp
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
//@+node:gcross.20110203233241.1537: ** << Includes >>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>

#include "illuminate/color_codes.hpp"
#include "illuminate/test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1624: ** << Usings >>
using boost::any;
using boost::equals;
using boost::format;
using boost::program_options::invalid_option_value;
namespace validators = boost::program_options::validators;
using boost::to_lower;

using std::endl;
using std::string;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1540: ** struct ColorCodes
//@+node:gcross.20110809112154.2057: *3* (constructors)
ColorCodes::ColorCodes(string const& suite, string const& test, string const& skip, string const& pass, string const& fail, string const& reset)
    : suite(suite)
    , test(test)
    , skip(skip)
    , pass(pass)
    , fail(fail)
    , reset(reset)
{ }
//@+node:gcross.20110809112154.2058: *3* (static fields)
ColorCodes const ColorCodes::plain("","","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;35m","\033[1;32m","\033[1;31m","\033[0;0m");
//@+node:gcross.20110809112154.2060: *3* failed
format ColorCodes::failed() const {
    return format("%1%FAILED :-(%2%") % fail % reset;
}
//@+node:gcross.20110809112154.2061: *3* failure
format ColorCodes::failure(string const& m) const {
    return format("    %1%* %2%%3%") % fail % m % reset;
}
//@+node:gcross.20110809112154.2056: *3* passed
format ColorCodes::passed() const {
    return format("%1%PASSED :-)%2%") % pass % reset;
}
//@+node:gcross.20110809112154.2078: *3* numberOfFailedTests
format ColorCodes::numberOfFailedTests(unsigned int const number_of_failed_tests) const {
    switch(number_of_failed_tests) {
        case 0:  return format("%1%%2%%3%") % pass % "All tests passed!" % reset;
        case 1:  return format("%1%%2%%3%") % fail % "1 test failed."    % reset;
        default: return format("%1%%2%%3%%4%") % fail % number_of_failed_tests % " tests failed." % reset;
    }
}
//@+node:gcross.20110809112154.2065: *3* suiteEntered
format ColorCodes::suiteEntered(Suite const& s) const {
    return format(suite + s.name + ":" + reset);
}
//@+at
//     return format("%1%%2%:%3%")
//         % suite
//         % s.name
//         % reset
//     ;
// }
//@+node:gcross.20110809112154.2076: *3* testName
format ColorCodes::testName(Test const& t) const {
    return format("%1%%2% [#%3%]%4%")
        % test
        % t.name
        % t.id
        % reset
    ;
}
//@+node:gcross.20110809112154.2077: *3* testNameAndSkipped
format ColorCodes::testNameAndSkipped(Test const& t) const {
    return format("%1%%2% [#%3%] %4%%5%")
        % test
        % t.name
        % t.id
        % (t.skipped ? " (skipped)" : "")
        % reset
    ;
}
//@+node:gcross.20110809112154.2064: *3* testSkipped
format ColorCodes::testSkipped() const {
    return format("%1%... %2%(skipped)%3%") % test % skip % reset;
}
//@+node:gcross.20110809112154.2062: *3* testStarted
format ColorCodes::testStarted() const {
    return format("%1%... %2%") % test % reset;
}
//@+node:gcross.20110204202041.1567: ** function validate
void validate(any& v
             ,vector<std::string> const& values
             ,Coloring* target_type
             ,int
             )
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
