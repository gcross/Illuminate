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
using boost::any;
using boost::function;
using boost::none;
using boost::optional;
using boost::packaged_task;
using boost::shared_ptr;
using boost::thread_specific_ptr;
using boost::unique_future;

using std::list;
using std::queue;
using std::string;
using std::vector;
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
    Suite const* const parent;
    string const name, full_name;
    bool const skipped;
    //@+node:gcross.20101205182001.2576: *4* (constructors)
    Node(string const& name, Suite const* parent, optional<bool> skipped=none);
    //@-others
};
//@+node:gcross.20101205182001.2583: *3* Suite
class Suite : public Node {
//@+others
//@+node:gcross.20101205182001.2584: *4* (friends)
friend class Test;
//@+node:gcross.20101205182001.2585: *4* (constructors)
public:

    Suite(string const& name, Suite const* parent, optional<bool> skipped=none);
//@+node:gcross.20101205182001.2586: *4* (fields)
private:

    list<Suite> nested_suites;
    vector<Test*> tests;
//@+node:gcross.20101205182001.2587: *4* (methods)
public:

    Suite& lookupSuite(string const& name, optional<bool> skipped=none);
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
        int const id;
        function<void ()> const runner;
        static thread_specific_ptr<vector<string> > current_failures;
        static FatalityMode fatality_mode;
    //@+node:gcross.20101206161648.1514: *4* (exceptions)
    public:
        struct FailuresAccessedOutsideTestContext : public std::exception { virtual char const* what() const throw(); };
        struct FatalTestFailure { };
    //@+node:gcross.20101205182001.2593: *4* (constructors)
    public:
        Test(string const& name, Suite& parent, function<void ()> runner, optional<bool> skipped=none);
    //@+node:gcross.20101205182001.2594: *4* (methods)
    protected:
        static vector<string>& getFailures();
    public:
        static string annotateFailureMessage(char const* filename, int line_number, string const& message);
        static unsigned int countFailures();
        static void die();
        static void eraseFailuresAfter(unsigned int number_of_failures);
        static void registerFailure(string const& message, bool fatal=false);
        static void registerFailure(char const* filename, unsigned int line_number, string const& message, bool fatal=false);
        TestResult operator()() const;
    //@-others
};
//@+node:gcross.20101205182001.2596: *3* Visitor
class Visitor {
    friend class Suite;
protected:
    virtual void enter(Suite const& suite) = 0;
    virtual void exit(Suite const& suite) = 0;
    virtual void test(Test const& test) = 0;
};
//@+node:gcross.20110203224841.1945: *3* ResultVisitor
class ResultVisitor : public virtual Visitor {
protected:
    virtual void testSkipped(Test const& test) = 0;
    virtual void testStarted(Test const& test) = 0;
    virtual void testPassed(Test const& test) = 0;
    virtual void testFailed(Test const& test,vector<string> const& failures) = 0;
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
