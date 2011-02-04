//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1835: * @thin queuer.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_QUEUER_HPP
#define ILLUMINATE_VISITORS_QUEUER_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1836: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1837: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1838: ** class Queuer
class QueuerVisitor : public Visitor {
    friend void enqueueTests(const TestQueue& queue, const TestFutures& futures, const Suite& suite);
protected:
    TestQueue queue;
    TestFutures futures;
    virtual void enter(const Suite& suite);
    virtual void exit(const Suite& suite);
    virtual void test(const Test& test);
private:
    QueuerVisitor(const TestQueue& queue, const TestFutures& futures);
};
//@+node:gcross.20101206161648.1858: ** function enqueueTests
void enqueueTests(const TestQueue& queue, const TestFutures& futures, const Suite& suite=getRoot());
//@-others

}

#endif
//@-leo
