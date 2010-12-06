//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1418: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1419: ** << Includes >>
#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1420: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1421: ** class Test
//@+node:gcross.20101205182001.1422: *3* (constructors)
Test::Test(const string& name, Suite& parent, function<void ()> runner)
    : Node(name,&parent)
    , test_id(getRoot().registerTest(this))
    , runner(runner)
{
    parent.tests.push_back(this);
}
//@+node:gcross.20101206142257.1467: *3* (static fields)
thread_specific_ptr<vector<string> > Test::current_failures;
//@+node:gcross.20101206142257.1395: *3* run
auto_ptr<vector<string> > Test::run() const {
    current_failures.reset(new vector<string>());
    runner();
    auto_ptr<vector<string> > failures(current_failures.get());
    current_failures.release();
    return failures;
}
//@-others

}
//@-leo
