//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1418: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1419: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1420: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1421: ** class Test
//@+node:gcross.20101205182001.1422: *3* (constructors)
Test::Test(const string& name, Suite& parent)
    : Node(name,&parent)
    , test_id(getRoot().registerTest(this))
{
    parent.tests.push_back(this);
}
//@-others

}
//@-leo
