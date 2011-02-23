//@+leo-ver=5-thin
//@+node:gcross.20101205182001.2567: * @thin core.hpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110222175650.1654: ** << License >>
//@+at
// ISC License (http://www.opensource.org/licenses/isc-license)
// 
// Copyright (c) 2011, Gregory Crosswhite <gcrosswhite@gmail.com>
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//@@c
//@-<< License >>

#ifndef ILLUMINATE_CORE_HPP
#define ILLUMINATE_CORE_HPP

//@+<< Includes >>
//@+node:gcross.20101205182001.2569: ** << Includes >>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <exception>
#include <list>
#include <queue>
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
//@+node:gcross.20110204202041.1562: ** exception FatalError
struct FatalError : public std::exception {
    string const message;
    FatalError(string const& message) : message(message) {}
    virtual ~FatalError() throw() {}
    char const* what() const throw() { return message.c_str(); }
};
//@+node:gcross.20101206161648.1861: ** Type aliases
typedef shared_ptr<vector<string> > TestResult;
typedef shared_ptr<packaged_task<TestResult> > TestTask;
typedef shared_ptr<queue<TestTask> > TestQueue;
typedef shared_ptr<unique_future<TestResult> > TestFuture;
typedef shared_ptr<vector<TestFuture> > TestFutures;
//@+node:gcross.20110204202041.1558: ** Enums
enum FatalityMode {NONE_FATAL, EXCEPTIONS_FATAL, ALL_FATAL};
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
    const bool skipped;
    //@+node:gcross.20101205182001.2576: *4* (constructors)
    Node(const string& name, Suite* parent, optional<bool> skipped=none);
    //@-others
};
//@+node:gcross.20101205182001.2583: *3* Suite
class Suite : public Node {
//@+others
//@+node:gcross.20101205182001.2584: *4* (friends)
friend class Test;
//@+node:gcross.20101205182001.2585: *4* (constructors)
public:

    Suite(const string& name, Suite* parent, optional<bool> skipped=none);
//@+node:gcross.20101205182001.2586: *4* (fields)
private:

    list<Suite> nested_suites;
    vector<Test*> tests;
//@+node:gcross.20101205182001.2587: *4* (methods)
public:

    Suite& lookupSuite(const string& name,const optional<bool> skipped=none);
    void visit(Visitor& visitor) const;
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
        const int id;
        const function<void ()> runner;
        static thread_specific_ptr<vector<string> > current_failures;
        static FatalityMode fatality_mode;
    //@+node:gcross.20101206161648.1514: *4* (exceptions)
    public:
        struct FailuresAccessedOutsideTestContext : public std::exception { virtual const char* what() const throw(); };
        struct FatalTestFailure { };
    //@+node:gcross.20101205182001.2593: *4* (constructors)
    public:
        Test(const string& name, Suite& parent, function<void ()> runner, optional<bool> skipped=none);
    //@+node:gcross.20101205182001.2594: *4* (methods)
    protected:
        static vector<string>& getFailures();
    public:
        static string annotateFailureMessage(const char* filename, int line_number, const string& message);
        static unsigned int countFailures();
        static void die();
        static void eraseFailuresAfter(unsigned int number_of_failures);
        static void registerFailure(const string& message, bool fatal=false);
        static void registerFailure(const char* filename, unsigned int line_number, const string& message, bool fatal=false);
        TestResult operator()() const;
    //@-others
};
//@+node:gcross.20101205182001.2596: *3* Visitor
class Visitor {
    friend class Suite;
protected:
    virtual void enter(const Suite& suite) = 0;
    virtual void exit(const Suite& suite) = 0;
    virtual void test(const Test& test) = 0;
};
//@+node:gcross.20110203224841.1945: *3* ResultVisitor
class ResultVisitor : public virtual Visitor {
protected:
    virtual void testSkipped(const Test& test) = 0;
    virtual void testStarted(const Test& test) = 0;
    virtual void testPassed(const Test& test) = 0;
    virtual void testFailed(const Test& test,const vector<string>& failures) = 0;
};
//@-others
//@+node:gcross.20101205182001.2588: ** Functions
//@+node:gcross.20101205214942.2483: *3* getRoot
Root& getRoot();
//@+node:gcross.20101206104532.1371: *3* underscoresToSpaces
string underscoresToSpaces(const string& old_string);
//@+node:gcross.20110204202041.1559: *3* validate
void validate(
      any& v
    , const vector<std::string>& values
    , FatalityMode* target_type
    , int
);
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
