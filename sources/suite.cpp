//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1306: * @thin suite.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1307: ** << Includes >>
#include <boost/foreach.hpp>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1314: ** << Usings >>
using namespace boost;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1308: ** struct Suite
//@+node:gcross.20101205182001.1313: *3* (constructors)
Suite::Suite(const string& name, const Suite* parent)
    : Node(name,parent)
{ }
//@+node:gcross.20101205182001.1319: *3* lookupSuite
Suite& Suite::lookupSuite(const string& name) {
    BOOST_FOREACH(Suite& suite, nested_suites) {
        if(suite.name == name) { return suite; }
    }
    nested_suites.push_back(Suite(name,this));
    return *(--nested_suites.end());
}
//@+node:gcross.20101205182001.1316: *3* visit
void Suite::visit(Visitor& visitor) {
    visitor.enter(*this);
    BOOST_FOREACH(Suite& suite, nested_suites) {
        suite.visit(visitor);
    }
    visitor.exit(*this);
    BOOST_FOREACH(Test* test, tests) {
        visitor.test(*test);
    }
}
//@+node:gcross.20101205214942.2484: ** getRoot
Suite& getRoot() { return getParentSuite(); }
//@-others

}

//@+<< Outside Namespace >>
//@+node:gcross.20101205214942.2497: ** << Outside Namespace >>
//@+others
//@+node:gcross.20101205214942.2499: *3* getParentSuite
Illuminate::Suite& getParentSuite() {
    static Illuminate::Suite root("Root",NULL);
    return root;
}
//@-others
//@-<< Outside Namespace >>
//@-leo
