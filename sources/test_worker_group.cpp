//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1547: * @file test_worker_group.cpp
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
//@+node:gcross.20101208142631.1548: ** << Includes >>
#include <boost/make_shared.hpp>

#include "illuminate/runners.hpp"
#include "illuminate/test_worker_group.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1549: ** << Usings >>
using boost::make_shared;
using boost::mutex;
using boost::optional;
using boost::unordered_map;

using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1550: ** class TestWorkerGroup
//@+node:gcross.20101208142631.1551: *3* (constructors)
TestWorkerGroup::TestWorkerGroup(
    unsigned int const number_of_workers,
    TestResultFetcher fetchResult,
    optional<vector<unsigned int> const&> maybe_test_ids
)
    : queue(new std::queue<TestTask>)
    , queue_mutex(new mutex)
    , futures(make_shared<unordered_map<unsigned int,TestFuture> >())
{
    if(maybe_test_ids) {
        enqueueSelectedTests(queue,futures,*maybe_test_ids);
    } else {
        enqueueAllTests(queue,futures);
    }
    for(unsigned int i = 0; i < number_of_workers; ++i) {
        workers.create_thread(TestWorker(queue,queue_mutex,fetchResult));
    }
}
//@+node:gcross.20101208142631.1553: *3* (destructors)
TestWorkerGroup::~TestWorkerGroup()
{
    workers.interrupt_all(); 
}
//@-others

}
//@-leo
