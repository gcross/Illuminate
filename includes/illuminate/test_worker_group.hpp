//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1491: * @thin test_worker_group.hpp
//@@language cplusplus

#ifndef ILLUMINATE_TEST_WORKER_GROUP_HPP
#define ILLUMINATE_TEST_WORKER_GROUP_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1492: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate/core.hpp"
#include "illuminate/test_worker.hpp"
#include "illuminate/visitors/test_queue.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1493: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1494: ** class TestWorkerGroup
class TestWorkerGroup {
protected:
    TestQueue queue;
    shared_ptr<mutex> queue_mutex;
    shared_ptr<bool> stop_signal;
public:
    TestFutures futures;
    thread_group workers;

    TestWorkerGroup(const int number_of_workers);
    ~TestWorkerGroup();
};
//@-others

}

#endif
//@-leo
