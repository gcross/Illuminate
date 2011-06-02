//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1499: * @file test_worker.hpp
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

#ifndef ILLUMINATE_TEST_WORKER_HPP
#define ILLUMINATE_TEST_WORKER_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1500: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "task.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1502: ** class TestWorker
//! A worker for running tests
class TestWorker {
public:
    //! Constructor
    TestWorker(
        //! queue of test tasks
        TestQueue const& queue,
        //! a mutex that should be locked to access the queue
        boost::shared_ptr<boost::mutex> const& queue_mutex,
        //! a value that signals the worker to halt when set to true
        boost::shared_ptr<const bool> const& stop_signal
    );
    
    //! Run the worker.
    void operator()();
protected:
    //! queue of test tasks
    TestQueue queue;
    //! a mutex that is locked before accessing the test queue
    boost::shared_ptr<boost::mutex> queue_mutex;
    //! a value that signals the worker to halt when set to true
    boost::shared_ptr<const bool> stop_signal;
};
//@-others

}

#endif
//@-leo
