//@+leo-ver=5-thin
//@+node:gcross.20101205182001.2567: * @thin core.hpp
//@@language cplusplus

#ifndef ILLUMINATE_CORE_HPP
#define ILLUMINATE_CORE_HPP

//@+<< Includes >>
//@+node:gcross.20101205182001.2569: ** << Includes >>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <exception>
#include <list>
#include <memory>
#include <string>
#include <vector>
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1315: ** << Usings >>
using namespace boost;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1861: ** Type aliases
typedef auto_ptr<vector<string> > TestResult;
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
//@+node:gcross.20101206104532.1407: *3* Root
class Root : public Suite {
//@+others
//@+node:gcross.20101206104532.1411: *4* (friends)
friend Root& getRoot();
//@+node:gcross.20101206104532.1408: *4* (fields)
public:
    vector<Test*> tests;
//@+node:gcross.20101206104532.1409: *4* (constructors)
private:
    Root();
//@+node:gcross.20101206104532.1410: *4* (methods)
public:
    int registerTest(Test* test);
//@-others
};
//@+node:gcross.20101205182001.2592: *3* Test
class Test : public Node {
    //@+others
    //@+node:gcross.20101206104532.1412: *4* (fields)
    public:
        const int test_id;
        const function<void ()> runner;
        static thread_specific_ptr<vector<string> > current_failures;
    //@+node:gcross.20101206161648.1514: *4* (exceptions)
    struct FailureRegisteredOutsideTestContext : public std::exception { virtual const char* what() const throw(); };
    struct FatalTestFailure { };
    //@+node:gcross.20101205182001.2593: *4* (constructors)
    public:
        Test(const string& name, Suite& parent, function<void ()> runner);
    //@+node:gcross.20101205182001.2594: *4* (methods)
    public:
        static string annotateFailureMessage(const char* filename, int line_number, const string& message);
        static void die();
        static void registerFailure(const string& message);
        static void registerFailure(const char* filename, int line_number, const string& message);
        static void registerFatalFailure(const string& message);
        static void registerFatalFailure(const char* filename, int line_number, const string& message);
        TestResult run() const;
    //@-others
};
//@+node:gcross.20101205182001.2596: *3* Visitor
class Visitor {
    friend class Suite;
protected:
    virtual void enter(const Suite& suite) = 0;
    virtual void exit(const Suite& suite) = 0;
    virtual void test(Test& suite) = 0;
};
//@-others
//@+node:gcross.20101205182001.2588: ** Functions
//@+node:gcross.20101205214942.2483: *3* getRoot
Root& getRoot();
//@+node:gcross.20101206104532.1371: *3* underscoresToSpaces
string underscoresToSpaces(const string& old_string);
//@-others

}

//@+<< Outside Namespace >>
//@+node:gcross.20101205214942.2488: ** << Outside Namespace >>
//@+others
//@+node:gcross.20101205214942.2491: *3* Functions
//@+node:gcross.20101205214942.2493: *4* getParentSuite
Illuminate::Suite& getParentSuite();
//@-others
//@-<< Outside Namespace >>

#endif
//@-leo
