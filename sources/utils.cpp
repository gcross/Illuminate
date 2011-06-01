//@+leo-ver=5-thin
//@+node:gcross.20101206104532.1377: * @thin utils.cpp
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
//@+node:gcross.20101206104532.1378: ** << Includes >>
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>

#include "illuminate/test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206104532.1379: ** << Usings >>
using boost::trim;

using std::string;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206104532.1382: ** Functions
//@+node:gcross.20101206104532.1384: *3* underscoresToSpaces
string underscoresToSpaces(string const& old_string) {
    string new_string = old_string;
    BOOST_FOREACH(char& c, new_string) {
        if(c == '_') { c = ' '; }
    }
    trim(new_string);
    return new_string;
}
//@-others

}
//@-leo
