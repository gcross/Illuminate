//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1573: * @thin future.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_RESULT_FUTURE_HPP
#define ILLUMINATE_VISITORS_RESULT_FUTURE_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1574: ** << Includes >>
#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1575: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1577: ** class FutureResultVisitor
class FutureResultVisitor : public virtual ResultVisitor {
public:
    unsigned int number_of_failed_tests;
protected:
    TestFutures futures;
    FutureResultVisitor(const TestFutures& futures);
    virtual void test(const Test& test);
};
//@-others

}

#endif
//@-leo
