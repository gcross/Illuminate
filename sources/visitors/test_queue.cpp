//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1848: * @thin test_queue.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206161648.1849: ** << Includes >>
#include <iostream>

#include "illuminate/visitors/test_queue.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1850: ** << Usings >>
using namespace boost;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1851: ** class TestQueuer
//@+node:gcross.20101206161648.1852: *3* (constructors)
TestQueuer::TestQueuer(const TestQueue& queue, const TestFutures& futures)
    : queue(queue)
    , futures(futures)
{ }
//@+node:gcross.20101206161648.1853: *3* enter
void TestQueuer::enter(const Suite& suite_) { }
//@+node:gcross.20101206161648.1854: *3* exit
void TestQueuer::exit(const Suite& suite) { }
//@+node:gcross.20101206161648.1860: *3* test
void TestQueuer::test(const Test& test) {
    TestTask task(new packaged_task<TestResult>(test));
    TestFuture future(new unique_future<TestResult>);
    (*future) = task->get_future();
    (*futures)[test.id] = future;
    queue->push(task);
}
//@+node:gcross.20101208142631.1486: ** function enqueueTests
void enqueueTests(const TestQueue& queue, const TestFutures& futures, const Suite& suite) {
    TestQueuer queuer(queue,futures);
    suite.visit(queuer);
}
//@-others

}
//@-leo
