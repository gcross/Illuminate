//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1573: * @thin future.hpp
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

#ifndef ILLUMINATE_VISITORS_RESULT_FUTURE_HPP
#define ILLUMINATE_VISITORS_RESULT_FUTURE_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1574: ** << Includes >>
#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1575: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1577: ** class FutureResultVisitor
class FutureResultVisitor : public virtual ResultVisitor {
public:
    unsigned int number_of_failed_tests;
protected:
    TestFutures futures;
    FutureResultVisitor(TestFutures const& futures);
    virtual void test(Test const& test);
};
//@-others

}

#endif
//@-leo
