//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1573: * @thin test_future.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_TEST_FUTURE_HPP
#define ILLUMINATE_VISITORS_TEST_FUTURE_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1574: ** << Includes >>
#include <iostream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1575: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1577: ** class TestFutureVisitor
class TestFutureVisitor : public virtual Visitor {
public:
    int number_of_failed_tests;
protected:
    TestFutures futures;
    TestFutureVisitor(const TestFutures& futures);
    virtual void test(const Test& test);
    virtual void testStarted(const Test& test) = 0;
    virtual void testPassed(const Test& test) = 0;
    virtual void testFailed(const Test& test,const vector<string>& failures) = 0;
};
//@-others

}

#endif
//@-leo
