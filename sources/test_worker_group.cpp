//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1547: * @thin test_worker_group.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101208142631.1548: ** << Includes >>
#include "illuminate/test_worker_group.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1549: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1550: ** class TestWorkerGroup
//@+node:gcross.20101208142631.1551: *3* (constructors)
TestWorkerGroup::TestWorkerGroup(const int number_of_workers)
    : queue(new std::queue<TestTask>)
    , queue_mutex(new mutex)
    , futures(new vector<TestFuture>(getRoot().tests.size()))
    , stop_signal(new bool)
{
    *stop_signal = false;
    enqueueTests(queue,futures);
    for(int i = 0; i < number_of_workers; ++i) {
        workers.create_thread(TestWorker(queue,queue_mutex,stop_signal));
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
