//@+leo-ver=5-thin
//@+node:gcross.20110809112154.2422: * @file exceptions.cpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110809112154.2424: ** << License >>
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
//@+node:gcross.20110809112154.2426: ** << Includes >>
#include <boost/format.hpp>

#include "illuminate/exceptions.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110809112154.2428: ** << Usings >>
using boost::format;

using std::exception;
using std::string;
//@-<< Usings >>

//@+others
//@+node:gcross.20110809112154.2431: ** Exceptions
//@+node:gcross.20110809112154.2432: *3* TestIdTooLargeException
TestIdTooLargeException::TestIdTooLargeException(unsigned int test_id, unsigned int maximum_test_id)
  : test_id(test_id)
  , maximum_test_id(maximum_test_id)
  , message((format("No such test id %1% (%1% > %2%).") % test_id % maximum_test_id).str())
{}

char const* TestIdTooLargeException::what() const throw() {
    return message.c_str();
}
TestIdTooLargeException::~TestIdTooLargeException() throw() {}
//@-others

}
//@-leo
