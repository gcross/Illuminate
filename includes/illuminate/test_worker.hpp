//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1499: * @thin test_worker.hpp
//@@language cplusplus

#ifndef ILLUMINATE_TEST_WORKER_HPP
#define ILLUMINATE_TEST_WORKER_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1500: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1501: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1502: ** class TestWorker
class TestWorker {
public:
    TestWorker(const TestQueue& queue, const shared_ptr<mutex>& queue_mutex, const shared_ptr<const bool>& stop_signal);
    void operator()();
protected:
    TestQueue queue;
    shared_ptr<mutex> queue_mutex;
    shared_ptr<const bool> stop_signal;
};
//@-others

}

#endif
//@-leo
