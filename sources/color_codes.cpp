//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1536: * @thin color_codes.cpp
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
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1624: ** << Usings >>
using boost::any;
using boost::equals;
using boost::program_options::invalid_option_value;
namespace validators = boost::program_options::validators;
using boost::to_lower;

using std::string;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1540: ** struct ColorCodes
ColorCodes::ColorCodes(string const& suite, string const& test, string const& skip, string const& pass, string const& fail, string const& reset)
    : suite(suite)
    , test(test)
    , skip(skip)
    , pass(pass)
    , fail(fail)
    , reset(reset)
{ }

ColorCodes const ColorCodes::plain("","","","","",""), ColorCodes::ANSI("\033[0m","\033[1;33m","\033[1;35m","\033[1;32m","\033[1;31m","\033[0;0m");
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
