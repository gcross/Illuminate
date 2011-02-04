//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1602: * @thin runner.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_RESULT_RUNNER_HPP
#define ILLUMINATE_VISITORS_RESULT_RUNNER_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1603: ** << Includes >>
#include <ostream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1604: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1605: ** class RunnerResultVisitor
class RunnerResultVisitor : public virtual ResultVisitor {
public:
    unsigned int number_of_failed_tests;
protected:
    RunnerResultVisitor();
    virtual void test(const Test& test);
};
//@-others

}

#endif
//@-leo
