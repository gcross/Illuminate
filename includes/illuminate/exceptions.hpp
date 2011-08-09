//@+leo-ver=5-thin
//@+node:gcross.20110809112154.2413: * @file exceptions.hpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110809112154.2415: ** << License >>
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

#ifndef ILLUMINATE_EXCEPTIONS_HPP
#define ILLUMINATE_EXCEPTIONS_HPP

//@+<< Includes >>
//@+node:gcross.20110809112154.2417: ** << Includes >>
#include <exception>
#include <string>
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110809112154.2420: ** Exceptions
//@+node:gcross.20110809112154.2421: *3* TestIdTooLargeException
struct TestIdTooLargeException : std::exception {
    unsigned int test_id, maximum_test_id;
    std::string message;
    TestIdTooLargeException(unsigned int test_id, unsigned int maximum_test_id);
    virtual char const* what() const throw();
    virtual ~TestIdTooLargeException() throw();
};
//@-others

}

#endif
//@-leo
