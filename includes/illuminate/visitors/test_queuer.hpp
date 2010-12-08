//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1835: * @thin test_queuer.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_TEST_QUEUER_HPP
#define ILLUMINATE_VISITORS_TEST_QUEUER_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1836: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1837: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1857: ** Type aliases
typedef packaged_task<TestResult> TestTask;
typedef queue<TestTask> TestQueue;
typedef vector<unique_future<TestResult> > TestResults;
//@+node:gcross.20101206161648.1838: ** class TestQueuer
class TestQueuer : public Visitor {
    friend pair<TestQueue,TestResults> createTestQueue(Suite& suite);
protected:
    TestQueue& queue;
    TestResults& results;
    virtual void enter(const Suite& suite);
    virtual void exit(const Suite& suite);
    virtual void test(Test& test);
private:
    TestQueuer(TestQueue& queue, TestResults& results);
};
//@+node:gcross.20101206161648.1858: ** function createTestQueue
pair<TestQueue,TestResults> createTestQueue(Suite& suite=getRoot());
//@-others

}

#endif
//@-leo
