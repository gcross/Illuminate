//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1517: * @thin test_worker.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101208142631.1518: ** << Includes >>
#include <sstream>

#include "illuminate/test_worker.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1519: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1536: ** class TestWorker
//@+node:gcross.20101208142631.1537: *3* (constructors)
TestWorker::TestWorker(const TestQueue& queue, const shared_ptr<mutex>& queue_mutex, const shared_ptr<const bool>& stop_signal)
    : queue(queue)
    , queue_mutex(queue_mutex)
    , stop_signal(stop_signal)
{ }
//@+node:gcross.20101208142631.1540: *3* operator()
void TestWorker::operator()() {
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
        (*task)();
    }
}
//@-others

}
//@-leo
