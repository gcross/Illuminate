/*! \file result.hpp
    \brief Illuminate::ResultVisitor class
*/

#ifndef ILLUMINATE_VISITORS_RESULT_HPP
#define ILLUMINATE_VISITORS_RESULT_HPP

// Includes {{{
#include <boost/function.hpp>

#include "../visitor.hpp"
// }}}

namespace Illuminate {

//! Test result visitor.
/*!
This class extends the Visitor interface with additional methods that are called with information about the result of running a test.
*/
class ResultVisitor : public virtual Visitor { // {{{
protected:
    //! The processor that will be used to process tests.
    TestResultFetcher fetchTestResult;

    //! Constructor
    /*! \param fetchTestResult function that should be used to fetch test results */
    ResultVisitor(TestResultFetcher const& fetchTestResult);

    //! Called when a test has been skipped.
    virtual void testSkipped(Test const& test) = 0;
    //! Called when a test has been started.
    virtual void testStarted(Test const& test) = 0;
    //! Called when a test has been passed.
    virtual void testPassed(Test const& test) = 0;
    //! Called when a test has been failed.
    /*!
    \param test the test that failed
    \param failures a list of descriptions of the failures that were recorded for the test
    */
    virtual void testFailed(Test const& test,std::vector<std::string> const& failures) = 0;

public:
    //! Counter recording the number of observed failed tests
    unsigned int number_of_failed_tests;

    virtual void test(Test const& test);
}; // }}}

}

#endif
