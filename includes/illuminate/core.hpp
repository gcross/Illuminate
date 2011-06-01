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
//@+node:gcross.20110531213958.2792: *3* Test tree
//! \defgroup TestTree Test tree
//! @{

//@+others
//@+node:gcross.20101205182001.2574: *4* Node
//! A node in the test tree.
struct Node {
    //@+others
    //@+node:gcross.20101205182001.2575: *5* (fields)
    //! The parent of this node (may be null).
    optional<Suite const&> const parent;

    //! The name of this node.
    string const name;

    //! Whether to skip this node.
    bool const skipped;
    //@+node:gcross.20101205182001.2576: *5* (constructors)
    /*!
    \param name the name of this node
    \param parent the (optional) parent of this node
    \param skipped whether to skip this node;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Node(string const& name, optional<Suite const&> parent, optional<bool> skipped=none);
    //@-others
};
//@+node:gcross.20101205182001.2583: *4* Suite
//! A test suite.
class Suite : public Node {
    //@+others
    //@+node:gcross.20101205182001.2584: *5* (friends)
    friend class Test;
    //@+node:gcross.20101205182001.2585: *5* (constructors)
    public:

    /*!
    \param name the name of this suite
    \param parent the (optional) parent of this suite
    \param skipped whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Suite(string const& name, optional<Suite const&> parent, optional<bool> skipped=none);
    //@+node:gcross.20101205182001.2586: *5* (fields)
    private:

    //! List of child suites.
    list<Suite> nested_suites;

    //! List of child tests.
    vector<Test*> tests;
    //@+node:gcross.20101205182001.2587: *5* (methods)
    public:

    //! Look up (or possibly create) the child suite with the given \c name.
    /*!
    This method will attempt to find the child suite with the given name.  If no such child is found, then a new suite will be created with the given name and added to the list of child suites.
    \param name the name of the suite to look up
    \param skipped the value of \c skipped to use if a new suite is created
    \return the (possibly freshly created) child of this suite with the given name
    */
    Suite& lookupSuite(string const& name, optional<bool> skipped=none);

    //! Apply the visitor to this suite.
    /*!
    \param visitor the visitor to apply to this suite
    */
    void visit(Visitor& visitor) const;
    //@-others
};
//@+node:gcross.20101206104532.1407: *4* Root
//! The root of the test tree.
/*!
This class is a singleton that can be access by calling getRoot. 

\sa getRoot
*/
class Root : public Suite {
    //@+others
    //@+node:gcross.20101206104532.1411: *5* (friends)
    friend Root& getRoot();
    //@+node:gcross.20101206104532.1408: *5* (fields)
    public:

    //! A vector containing all registered tests.
    vector<Test*> tests;
    //@+node:gcross.20101206104532.1409: *5* (constructors)
    private:

    //! The private constructor --- private because this class is a singleton.
    Root();
    //@+node:gcross.20101206104532.1410: *5* (methods)
    public:

    //! Registers a test case in the global list.
    /*!
    \param test a pointer to the test case
    \return a unique integer identifier for the test
    */
    int registerTest(Test* test);
    //@-others
};
//@+node:gcross.20101205182001.2592: *4* Test
//! A test case.
class Test : public Node {
    //@+others
    //@+node:gcross.20101206104532.1412: *5* (fields)
    public:

    //! The unique identifier of the test.
    int const id;

    //! The code that performs the test.
    function<void ()> const runner;

    //! The list of failures that have been recorded in this thread for the current test being run.
    static thread_specific_ptr<vector<string> > current_failures;

    //! The "fatality mode", which specifies the types of errors that will be turned into fatal errors.
    static FatalityMode fatality_mode;
    //@+node:gcross.20101206161648.1514: *5* (exceptions)
    public:

    //! An exception thrown if the failure list is accessed outside the context of running a test.
    struct FailuresAccessedOutsideTestContext : public std::exception { virtual char const* what() const throw(); };

    private:

    //! An exception thrown when an error is a fatal error (as determined by Test::fatality_mode).
    struct FatalTestFailure { };
    //@+node:gcross.20101205182001.2593: *5* (constructors)
    public:

    /*!
    \param name the name of the test
    \param parent the parent of this suite
    \param runner the code of the test
    \param skipped whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Test(string const& name, Suite& parent, function<void ()> runner, optional<bool> skipped=none);
    //@+node:gcross.20101205182001.2594: *5* (methods)
    protected:

    //! Get the (thread-local) current list of failures.
    static vector<string>& getFailures();

    public:

    //! Construct a failure message annotated with source position infomration.
    /*!
    \param filename the name of the source file
    \param line_number the line number of the source file
    \param message the message describing the failure
    \return \c message annotated with the information supplied in \c filename and \c line_number
    */
    static string annotateFailureMessage(char const* filename, int line_number, string const& message);

    //! Returns the (thread-local) current number of failures recorded.
    static unsigned int countFailures();

    //! Immediately terminates the current test.
    static void die();

    //! Erase all failures in the (thread-local) current failure list after \c number_of_failures.
    static void eraseFailuresAfter(unsigned int number_of_failures);

    //! Adds a failure with the given message to the (thread-local) current failure list.
    /*!
    \param message a message describing the nature of the failure
    \param whether the failure is fatal;  if true, then the test is terminated, if false then the test is allowed to proceed
    */
    static void registerFailure(string const& message, bool fatal=false);

    //! Adds a failure with an annotated message to the (thread-local) current failure list.
    /*!
    This method acts like Test::registerFailure(string const&,bool), but it first annotates the message with the provided information with the location of the failure in the source file using Test::annotateFailureMessage.
    \param filename the name of the source file
    \param line_number the line number of the source file
    \param message a message describing the nature of the failure
    \param whether the failure is fatal;  if true, then the test is terminated, if false then the test is allowed to proceed
    */
    static void registerFailure(char const* filename, unsigned int line_number, string const& message, bool fatal=false);

    //! Run this test and return the result.
    /*!
    \return the result of running the test
    */
    TestResult operator()() const;
    //@-others
};
//@-others

//! @}
//@+node:gcross.20110531213958.2793: *3* Visitor
//@+node:gcross.20101205182001.2596: *4* Visitor
class Visitor {
    friend class Suite;
protected:
    virtual void enter(Suite const& suite) = 0;
    virtual void exit(Suite const& suite) = 0;
    virtual void test(Test const& test) = 0;
};
//@+node:gcross.20110203224841.1945: *4* ResultVisitor
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
