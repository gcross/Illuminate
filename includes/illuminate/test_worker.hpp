#ifndef ILLUMINATE_TEST_WORKER_HPP
#define ILLUMINATE_TEST_WORKER_HPP

// Includes {{{
#include <boost/thread.hpp>
#include <iostream>

#include "task.hpp"
// }}}

namespace Illuminate {

//! A worker for running tests
class TestWorker { // {{{
public:
    //! Constructor
    TestWorker(
        //! queue of test tasks
        TestQueue const& queue,
        //! a mutex that should be locked to access the queue
        boost::shared_ptr<boost::mutex> const& queue_mutex,
        //! the fetcher to use for obtaining test results
        TestResultFetcher fetchResult=Test::run
    );
    
    //! Run the worker.
    void operator()();
protected:
    //! queue of test tasks
    TestQueue queue;
    //! a mutex that is locked before accessing the test queue
    boost::shared_ptr<boost::mutex> queue_mutex;
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult;
}; // }}}

}

#endif
