//@+leo-ver=5-thin
//@+node:gcross.20110601121230.1617: * @file visitor.hpp
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

/*! \file visitor.hpp
    \brief Illuminate::Visitor class
*/

#ifndef ILLUMINATE_VISITOR_HPP
#define ILLUMINATE_VISITOR_HPP

//@+<< Includes >>
//@+node:gcross.20110601121230.1618: ** << Includes >>
#include "test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101205182001.2596: ** class Visitor
//! Test tree visitor.
struct Visitor {
    //! Called when a suite has been entered.
    virtual void enter(Suite const& suite) = 0;
    //! Called when a suite has been exited.
    virtual void exit(Suite const& suite) = 0;
    //! Called to visit a test.
    virtual void test(Test const& test) = 0;
};
//@-others

}

#endif
//@-leo
