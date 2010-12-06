//@+leo-ver=5-thin
//@+node:gcross.20101205182001.2567: * @thin illuminate.hpp
//@@language cplusplus

#ifndef ILLUMINATE_HPP
#define ILLUMINATE_HPP

//@+<< Includes >>
//@+node:gcross.20101205182001.2569: ** << Includes >>
#include <list>
#include <string>
#include <vector>
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1315: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.2570: ** Classes
//@+<< Forward declarations >>
//@+node:gcross.20101205182001.2577: *3* << Forward declarations >>
class Node;
class Suite;
class Test;
class Visitor;
//@-<< Forward declarations >>

//@+others
//@+node:gcross.20101205182001.2574: *3* Node
struct Node {
    //@+others
    //@+node:gcross.20101205182001.2575: *4* (fields)
    const Suite* parent;
    const string name, full_name;
    //@+node:gcross.20101205182001.2576: *4* (constructors)
    Node(const string& name, const Suite* parent);
    //@-others
};
//@+node:gcross.20101205182001.2583: *3* Suite
class Suite : public Node {
//@+others
//@+node:gcross.20101205182001.2584: *4* (friends)
friend class Test;
//@+node:gcross.20101205182001.2585: *4* (constructors)
public:

    Suite(const string& name, const Suite* parent);
//@+node:gcross.20101205182001.2586: *4* (fields)
private:

    list<Suite> nested_suites;
    vector<Test*> tests;
//@+node:gcross.20101205182001.2587: *4* (methods)
public:

    Suite& lookupSuite(const string& name);
    void visit(Visitor& visitor);
//@-others
};
//@+node:gcross.20101205182001.2592: *3* Test
class Test : public Node {
    //@+others
    //@+node:gcross.20101205182001.2593: *4* (constructors)
    protected:
        Test(const string& name, Suite& parent);
    //@+node:gcross.20101205182001.2594: *4* (methods)
    //@-others
};
//@+node:gcross.20101205182001.2596: *3* Visitor
struct Visitor {
    virtual void enter(const Suite& suite) = 0;
    virtual void exit(const Suite& suite) = 0;
    virtual void test(Test& suite) = 0;
};
//@-others
//@+node:gcross.20101205182001.2588: ** Variables
extern Suite Parent;
//@-others

}

#endif
//@-leo
