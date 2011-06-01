//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1835: * @thin queuer.hpp
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

#ifndef ILLUMINATE_VISITORS_QUEUER_HPP
#define ILLUMINATE_VISITORS_QUEUER_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1836: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate/visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101206161648.1838: ** class Queuer
class QueuerVisitor : public Visitor {
    friend void enqueueTests(TestQueue const& queue, TestFutures const& futures, Suite const& suite);
protected:
    TestQueue queue;
    TestFutures futures;
    virtual void enter(Suite const& suite);
    virtual void exit(Suite const& suite);
    virtual void test(Test const& test);
private:
    QueuerVisitor(TestQueue const& queue, TestFutures const& futures);
};
//@+node:gcross.20101206161648.1858: ** function enqueueTests
void enqueueTests(TestQueue const& queue, TestFutures const& futures, Suite const& suite=getRoot());
//@-others

}

#endif
//@-leo
