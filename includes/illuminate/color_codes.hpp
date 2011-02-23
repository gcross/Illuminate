//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1528: * @thin color_codes.hpp
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

#ifndef ILLUMINATE_COLOR_CODES_HPP
#define ILLUMINATE_COLOR_CODES_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1529: ** << Includes >>
#include <boost/any.hpp>
#include <string>
#include <vector>
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1530: ** << Usings >>
using boost::any;

using std::string;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1531: ** struct ColorCodes
struct ColorCodes {
    ColorCodes(const string& suite, const string& test, const string& skip, const string& pass, const string& fail, const string& reset);
    string suite, test, skip, pass, fail, reset;
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
