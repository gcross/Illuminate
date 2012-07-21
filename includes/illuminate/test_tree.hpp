/*! \file test_tree.hpp
    \brief Classes that define the test tree.
*/

#ifndef ILLUMINATE_TEST_TREE_HPP
#define ILLUMINATE_TEST_TREE_HPP

// Includes {{{
#include <boost/any.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <exception>
#include <queue>
#include <string>
#include <vector>
// }}}

namespace Illuminate {

// Forward declarations {{{
class Suite;
class Test;
class Visitor;
// }}}

// Exceptions {{{

//! Exception thrown when a fatal error is encountered in a test
/*!
\note If thrown while running the body of a test, this does not terminate the program unless a fatality mode has been enabled, it just causes the test itself to immediately terminate.
*/
struct FatalError : public std::exception { // {{{
    //! The message decribing the failure.
    std::string const message;
    //! Constructor.
    FatalError(std::string const& message) : message(message) {}
    //! Destructor.
    virtual ~FatalError() throw() {}
    //! Returns the failure message.
    char const* what() const throw() { return message.c_str(); }
}; // }}}

// }}}
// Type aliases {{{

//! The result of executing a test.
/*!
If the vector is empty, then the test is deemed to have passed.  Otherwise, the test is deemed to have failed, and the vector contains a list of descriptions of the failures that were encountered and recorded.
*/
typedef boost::shared_ptr<std::vector<std::string> > TestResult;
//! Function which fetches the result of a test.
typedef boost::function<TestResult (unsigned int)> TestResultFetcher;

// }}}
// Enums {{{

//! A setting that specifies what kind of failure (if any) will cause the test program to abort.
/*!
One of the main motivations behind this feature is to make it easier for the user to inspect the code using a debugger to figure out what is going on when a test fails, since aborting the test program turns control back to the debugger and provides the user with a nice stack trace to help them figure out what is going on.
*/
enum AbortMode {
    //! The test program should never intentionally abort (though of course segfaults may force its hand!)
    NEVER_ABORT,
    //! The test program should abort if any uncaught exception is encountered.
    ABORT_ON_EXCEPTION,
    //! The test program should abort if any failure at all is encountered.
    ABORT_ON_ANY_FAILURE
};

// }}}
// Classes {{{

//! \defgroup TestTree Test tree
//! @{

//! A node in the test tree.
struct Node { // {{{
    // fields {{{

    //! The name of this node.
    std::string const name;

    //! The parent of this node (may be null).
    boost::optional<Suite const&> const parent;

    //! Whether to skip this node.
    bool const skipped;

    // }}}
    // constructors {{{

    //! Constructor
    Node(
        //! the name of this node
        std::string const& name,
        //! the (optional) parent of this node
        boost::optional<Suite const&> parent,
        //! whether to skip this node;  if not specified, this setting is copied from the \c skipped field of \c parent
        boost::optional<bool> skipped=boost::none
    );

    // }}}
}; // }}}
//! A test suite.
class Suite : public Node { // {{{
    // friends {{{

    friend class Test;

    // }}}
    // constructors {{{

    public:

    //! Constructor
    Suite(
        //! the name of this suite
        std::string const& name,
        //! the (optional) parent of this suite
        boost::optional<Suite const&> parent,
        //!  whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
        boost::optional<bool> skipped=boost::none
    );

    // }}}
    // fields {{{

    private:

    //! List of child suites.
    std::vector<Suite*> nested_suites;

    //! List of child tests.
    std::vector<Test*> tests;

    // }}}
    // methods {{{

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

    //! Construct a string representing the "path" of this suite.
    boost::format constructPath() const;

    //! Sort the children of this node.
    void sort();

    // }}}
}; // }}}
//! The root of the test tree.
/*!
This class is a singleton that can be access by calling getRoot. 

\sa getRoot
*/
class Root : public Suite { // {{{
    // friends {{{

    friend Root& getRoot();

    // }}}
    // fields {{{

    public:

    //! A vector containing all registered tests.
    std::vector<Test*> tests;

    // }}}
    // constructors {{{

    private:

    //! The private constructor --- private because this class is a singleton.
    Root();

    // }}}
    // methods {{{

    public:

    //! Registers a test case in the global list.
    /*!
    \param test a pointer to the test case
    \return a unique integer identifier for the test
    */
    unsigned int registerTest(Test* test);

    //! Returns a reference to the test with the given id.
    /*!
    \param id the test id
    \return a reference to the test with the given id
    */
    Test const& lookupTest(unsigned int id) const;

    //! Return the number of registered tests.
    unsigned int numberOfTests() const;

    //! Recursively sort all the tests and suites, and then renumber the tests.
    void sort();

    //! Exits with an error message if any of the test ids are invalid.
    void checkTestIds(std::vector<unsigned int> const& test_ids) const;

    // }}}
}; // }}}
//! A test case.
class Test : public Node { // {{{
    // fields {{{

    public:

    //! The unique identifier of the test.
    unsigned int id;

    //! The code that performs the test.
    boost::function<void ()> const runner;

    //! The list of failures that have been recorded in this thread for the current test being run.
    static boost::thread_specific_ptr<std::vector<std::string> > current_failures;

    //! The abort mode, which specifies the types of failures that will cause the test program to abort.
    static AbortMode abort_mode;

    // }}}
    // exceptions {{{

    public:

    //! An exception thrown if the failure list is accessed outside the context of running a test.
    struct FailuresAccessedOutsideTestContext : public std::exception {
        //! Returns a message describing this exception.
        virtual char const* what() const throw();
    };

    private:

    //! An exception thrown when an error is a fatal error (as determined by Test::abort_mode).
    struct FatalTestFailure { };

    // }}}
    // constructors {{{

    public:

    //! Constructor
    Test(
        //! the name of the test
        std::string const& name,
        //! the parent of this suite
        Suite& parent,
        //! the code of the test
        boost::function<void ()> runner,
        //! whether to skip this suite;  if not specified, this setting is copied from the \c skipped field of \c parent
        boost::optional<bool> skipped=boost::none
    );

    // }}}
    // methods {{{

    protected:

    //! Get the (thread-local) current list of failures.
    static std::vector<std::string>& getFailures();

    public:

    //! Construct a failure message annotated with source position infomration.
    static std::string annotateFailureMessage(
        //! the name of the source file
        char const* filename,
        //! the line number of the source file
        int line_number,
        //! the message describing the failure
        std::string const& message
    /*!
    \return \c message annotated with the information supplied in \c filename and \c line_number
    */
    );


    //! Returns the (thread-local) current number of failures recorded.
    static unsigned int countFailures();

    //! Immediately terminates the current test.
    static void die();

    //! Erase all failures in the (thread-local) current failure list after \c number_of_failures.
    static void eraseFailuresAfter(unsigned int number_of_failures);

    //! Adds a failure with the given message to the (thread-local) current failure list.
    static void registerFailure(
        //! a message describing the nature of the failure
        std::string const& message,
        //! whether the failure is fatal;  if true, then the test is terminated, if false then the test is allowed to proceed
        bool fatal=false
    );

    //! Adds a failure with an annotated message to the (thread-local) current failure list.
    /*!
    This method acts like Test::registerFailure(string const&,bool), but it first annotates the message with the provided information with the location of the failure in the source file using Test::annotateFailureMessage.
    */
    static void registerFailure(
        //! the name of the source file
        char const* filename,
        //! the line number of the source file
        unsigned int line_number,
        //! a message describing the nature of the failure
        std::string const& message,
        //! whether the failure is fatal;  if true, then the test is terminated, if false then the test is allowed to proceed
        bool fatal=false
    );

    //! Run this test and return the result.
    /*!
    \return the result of running the test
    */
    TestResult operator()() const;

    //! Run the test with the given id and return the result.
    static TestResult run(unsigned int test_id);

    //! Construct a string representing the "path" of this suite.
    boost::format constructPath() const;

    // }}}
}; // }}}

//! @}

// }}}
// Functions {{{

//! Returns a reference to the root of the test suite.
Root& getRoot();

//! Converts the underscores in a string to spaces, and removes leading underscores.
/*!
This function exists to allow a user to have spaces and non-leading-alphabetic characters in their test and suite names by using underscores in these places to turn their string into a valid C++ identifier and then using this function to convert this identifier back to the desired test or suite name.
\param old_string the input string
\return a copy of \c old_string with the underscores converted to spaces and any leading underscores removed.
*/
std::string underscoresToSpaces(const std::string& old_string);

//! Validates user input value for fatality modes.
/*!
\note This function is primarily intended to be used by boost::program_options.
*/
void validate(
      boost::any& v
    , const std::vector<std::string>& values
    , AbortMode* target_type
    , int
);


// }}}

}

// Outside namespace {{{
//! Returns the current parent suite in the global namespace, which is the root suite.
Illuminate::Suite& getParentSuite();
// }}}

#endif
