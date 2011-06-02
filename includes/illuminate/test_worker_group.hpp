//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1491: * @file test_worker_group.hpp
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

#ifndef ILLUMINATE_TEST_WORKER_GROUP_HPP
#define ILLUMINATE_TEST_WORKER_GROUP_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1492: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "future.hpp"
#include "test_worker.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1494: ** class TestWorkerGroup
//! A group of test workers
/*!
This class creates a group of worker threads which immediately start executing the tests in the global test tree and storing their results in \c futures.

\sa TestWorker
*/
class TestWorkerGroup {
protected:
    //! queue of test tasks
    TestQueue queue;
    //! a mutex that must be locked before accessing the test queue
    boost::shared_ptr<boost::mutex> queue_mutex;
    //! a value that signals the group of workers to halt when set to true
    boost::shared_ptr<bool> stop_signal;
public:
    //! futures providing the test results
    TestFutures futures;
    //! the thread group of the workers
    boost::thread_group workers;

    //! Constructor.
    //! \param number_of_workers number of workers to create
    TestWorkerGroup(unsigned int number_of_workers);
    
    //! Destructor.
    ~TestWorkerGroup();
};
//@-others

}

#endif
//@-leo
