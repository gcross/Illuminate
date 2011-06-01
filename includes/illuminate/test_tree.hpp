//@+leo-ver=5-thin
//@+node:gcross.20101205182001.2567: * @file test_tree.hpp
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

#ifndef ILLUMINATE_TEST_TREE_HPP
#define ILLUMINATE_TEST_TREE_HPP

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

//@+others
//@+node:gcross.20110204202041.1562: ** exception FatalError
struct FatalError : public std::exception {
    std::string const message;
    FatalError(std::string const& message) : message(message) {}
    virtual ~FatalError() throw() {}
    char const* what() const throw() { return message.c_str(); }
};
//@+node:gcross.20101206161648.1861: ** Type aliases
typedef boost::shared_ptr<std::vector<std::string> > TestResult;
typedef boost::shared_ptr<boost::packaged_task<TestResult> > TestTask;
typedef boost::shared_ptr<std::queue<TestTask> > TestQueue;
typedef boost::shared_ptr<boost::unique_future<TestResult> > TestFuture;
typedef boost::shared_ptr<std::vector<TestFuture> > TestFutures;
//@+node:gcross.20110204202041.1558: ** Enums
enum FatalityMode {NONE_FATAL, EXCEPTIONS_FATAL, ALL_FATAL};
//@+node:gcross.20101205182001.2570: ** Classes
//@+<< Forward declarations >>
//@+node:gcross.20101205182001.2577: *3* << Forward declarations >>
class Suite;
class Test;
class Visitor;
//@-<< Forward declarations >>

//! \defgroup TestTree Test tree
//! @{

//@+others
//@+node:gcross.20101205182001.2574: *3* Node
//! A node in the test tree.
struct Node {
    //@+others
    //@+node:gcross.20101205182001.2575: *4* (fields)
    //! The parent of this node (may be null).
    boost::optional<Suite const&> const parent;

    //! The name of this node.
    std::string const name;

    //! Whether to skip this node.
    bool const skipped;
    //@+node:gcross.20101205182001.2576: *4* (constructors)
    /*!
    \param name the name of this node
    \param parent the (optional) parent of this node
    \param skipped whether to skip this node;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Node(std::string const& name, boost::optional<Suite const&> parent, boost::optional<bool> skipped=boost::none);
    //@-others
};
//@+node:gcross.20101205182001.2583: *3* Suite
//! A test suite.
class Suite : public Node {
    //@+others
    //@+node:gcross.20101205182001.2584: *4* (friends)
    friend class Test;
    //@+node:gcross.20101205182001.2585: *4* (constructors)
    public:

    /*!
    \param name the name of this suite
    \param parent the (optional) parent of this suite
    \param skipped whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Suite(std::string const& name, boost::optional<Suite const&> parent, boost::optional<bool> skipped=boost::none);
    //@+node:gcross.20101205182001.2586: *4* (fields)
    private:

    //! List of child suites.
    std::list<Suite> nested_suites;

    //! List of child tests.
    std::vector<Test*> tests;
    //@+node:gcross.20101205182001.2587: *4* (methods)
    public:

    //! Look up (or possibly create) the child suite with the given \c name.
    /*!
    This method will attempt to find the child suite with the given name.  If no such child is found, then a new suite will be created with the given name and added to the list of child suites.
    \param name the name of the suite to look up
    \param skipped the value of \c skipped to use if a new suite is created
    \return the (possibly freshly created) child of this suite with the given name
    */
    Suite& lookupSuite(std::string const& name, boost::optional<bool> skipped=boost::none);

    //! Apply the visitor to this suite.
    /*!
    \param visitor the visitor to apply to this suite
    */
    void visit(Visitor& visitor) const;
    //@-others
};
//@+node:gcross.20101206104532.1407: *3* Root
//! The root of the test tree.
/*!
This class is a singleton that can be access by calling getRoot. 

\sa getRoot
*/
class Root : public Suite {
    //@+others
    //@+node:gcross.20101206104532.1411: *4* (friends)
    friend Root& getRoot();
    //@+node:gcross.20101206104532.1408: *4* (fields)
    public:

    //! A vector containing all registered tests.
    std::vector<Test*> tests;
    //@+node:gcross.20101206104532.1409: *4* (constructors)
    private:

    //! The private constructor --- private because this class is a singleton.
    Root();
    //@+node:gcross.20101206104532.1410: *4* (methods)
    public:

    //! Registers a test case in the global list.
    /*!
    \param test a pointer to the test case
    \return a unique integer identifier for the test
    */
    int registerTest(Test* test);
    //@-others
};
//@+node:gcross.20101205182001.2592: *3* Test
//! A test case.
class Test : public Node {
    //@+others
    //@+node:gcross.20101206104532.1412: *4* (fields)
    public:

    //! The unique identifier of the test.
    int const id;

    //! The code that performs the test.
    boost::function<void ()> const runner;

    //! The list of failures that have been recorded in this thread for the current test being run.
    static boost::thread_specific_ptr<std::vector<std::string> > current_failures;

    //! The "fatality mode", which specifies the types of errors that will be turned into fatal errors.
    static FatalityMode fatality_mode;
    //@+node:gcross.20101206161648.1514: *4* (exceptions)
    public:

    //! An exception thrown if the failure list is accessed outside the context of running a test.
    struct FailuresAccessedOutsideTestContext : public std::exception { virtual char const* what() const throw(); };

    private:

    //! An exception thrown when an error is a fatal error (as determined by Test::fatality_mode).
    struct FatalTestFailure { };
    //@+node:gcross.20101205182001.2593: *4* (constructors)
    public:

    /*!
    \param name the name of the test
    \param parent the parent of this suite
    \param runner the code of the test
    \param skipped whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
    */
    Test(std::string const& name, Suite& parent, boost::function<void ()> runner, boost::optional<bool> skipped=boost::none);
    //@+node:gcross.20101205182001.2594: *4* (methods)
    protected:

    //! Get the (thread-local) current list of failures.
    static std::vector<std::string>& getFailures();

    public:

    //! Construct a failure message annotated with source position infomration.
    /*!
    \param filename the name of the source file
    \param line_number the line number of the source file
    \param message the message describing the failure
    \return \c message annotated with the information supplied in \c filename and \c line_number
    */
    static std::string annotateFailureMessage(char const* filename, int line_number, std::string const& message);

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
    static void registerFailure(std::string const& message, bool fatal=false);

    //! Adds a failure with an annotated message to the (thread-local) current failure list.
    /*!
    This method acts like Test::registerFailure(string const&,bool), but it first annotates the message with the provided information with the location of the failure in the source file using Test::annotateFailureMessage.
    \param filename the name of the source file
    \param line_number the line number of the source file
    \param message a message describing the nature of the failure
    \param whether the failure is fatal;  if true, then the test is terminated, if false then the test is allowed to proceed
    */
    static void registerFailure(char const* filename, unsigned int line_number, std::string const& message, bool fatal=false);

    //! Run this test and return the result.
    /*!
    \return the result of running the test
    */
    TestResult operator()() const;
    //@-others
};
//@-others

//! @}
//@+node:gcross.20101205182001.2588: ** Functions
//@+node:gcross.20101205214942.2483: *3* getRoot
Root& getRoot();
//@+node:gcross.20101206104532.1371: *3* underscoresToSpaces
std::string underscoresToSpaces(const std::string& old_string);
//@+node:gcross.20110204202041.1559: *3* validate
void validate(
      boost::any& v
    , const std::vector<std::string>& values
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
