#ifndef ILLUMINATE_TEST_WORKER_GROUP_HPP
#define ILLUMINATE_TEST_WORKER_GROUP_HPP

// Includes {{{
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>

#include "future.hpp"
#include "test_worker.hpp"
// }}}

namespace Illuminate {

//! A group of test workers
/*!
This class creates a group of worker threads which immediately start executing the tests in the global test tree and storing their results in \c futures.

\sa TestWorker
*/
class TestWorkerGroup { // {{{
protected:
    //! queue of test tasks
    TestQueue queue;
    //! a mutex that must be locked before accessing the test queue
    boost::shared_ptr<boost::mutex> queue_mutex;
public:
    //! futures providing the test results
    TestFutures futures;
    //! the thread group of the workers
    boost::thread_group workers;

    //! Constructor.
    TestWorkerGroup(
        //! number_of_workers number of workers to create
        unsigned int number_of_workers,
        //! the fetcher to use for obtaining test results
        TestResultFetcher fetchResult=Test::run,
        //! the ids of the tests to run;  if none, then all tests are run
        boost::optional<std::vector<unsigned int> const&> maybe_test_ids=boost::none
    );
    
    //! Destructor.
    ~TestWorkerGroup();
}; // }}}

}

#endif
