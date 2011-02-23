//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1848: * @thin queuer.cpp
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
//@+node:gcross.20101206161648.1849: ** << Includes >>
#include <iostream>

#include "illuminate/visitors/queuer.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1850: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1851: ** class QueuerVisitor
//@+node:gcross.20101206161648.1852: *3* (constructors)
QueuerVisitor::QueuerVisitor(TestQueue const& queue, TestFutures const& futures)
    : queue(queue)
    , futures(futures)
{ }
//@+node:gcross.20101206161648.1853: *3* enter
void QueuerVisitor::enter(Suite const& suite_) { }
//@+node:gcross.20101206161648.1854: *3* exit
void QueuerVisitor::exit(Suite const& suite) { }
//@+node:gcross.20101206161648.1860: *3* test
void QueuerVisitor::test(Test const& test) {
    if(!test.skipped) {
        TestTask task(new packaged_task<TestResult>(test));
        TestFuture future(new unique_future<TestResult>);
        (*future) = task->get_future();
        (*futures)[test.id] = future;
        queue->push(task);
    }
}
//@+node:gcross.20101208142631.1486: ** function enqueueTests
void enqueueTests(TestQueue const& queue, TestFutures const& futures, Suite const& suite) {
    QueuerVisitor queuer(queue,futures);
    suite.visit(queuer);
}
//@-others

}
//@-leo
