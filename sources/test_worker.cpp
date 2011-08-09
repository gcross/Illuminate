//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1517: * @file test_worker.cpp
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
//@+node:gcross.20101208142631.1518: ** << Includes >>
#include <sstream>

#include "illuminate/test_worker.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1519: ** << Usings >>
using boost::lock_guard;
using boost::mutex;
namespace this_thread = boost::this_thread;
using boost::shared_ptr;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1536: ** class TestWorker
//@+node:gcross.20101208142631.1537: *3* (constructors)
TestWorker::TestWorker(TestQueue const& queue, shared_ptr<mutex> const& queue_mutex)
    : queue(queue)
    , queue_mutex(queue_mutex)
{ }
//@+node:gcross.20101208142631.1540: *3* operator()
void TestWorker::operator()() {
    Root const& root = getRoot();
    while(!this_thread::interruption_requested()) {
        TestTask task;
        {
            lock_guard<mutex> guard(*queue_mutex);
            if(queue->empty()) {
                return;
            } else {
                task = queue->front();
                queue->pop();
            }
        }
        task.second->set_value(root.lookupTest(task.first)());
    }
}
//@-others

}
//@-leo
