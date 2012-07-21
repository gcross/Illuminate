/*! \file runners.hpp
    \brief Standard test runners supplied by Illuminate.
*/

#ifndef ILLUMINATE_RUNNERS_HPP
#define ILLUMINATE_RUNNERS_HPP

// Includes {{{
#include <algorithm>
#include <boost/optional.hpp>
#include <iostream>

#include "color_codes.hpp"
#include "future.hpp"
#include "task.hpp"
#include "test_tree.hpp"
// }}}

namespace Illuminate {

// Functions {{{
/*! \defgroup TestRunners Runners
    \brief A collection of functions that operate on the global test tree.
    @{
*/
//! Populates a test queue and test futures with the tests in a given suite.
void enqueueAllTests( // {{{
    //! reference to the output test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the output test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! reference to the input test suite (which defaults to the root)
    Illuminate::Suite const& suite=getRoot()
); // }}}

//! Populates a test queue and test futures with the tests with the given ids.
void enqueueSelectedTests( // {{{
    //! reference to the output test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the output test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! reference to the test ids to be enqueued
    std::vector<unsigned int> const& test_ids
); // }}}

//! Enqueues the test with the given id
void enqueueTest( // {{{
    //! reference to the test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! the id of the test to be enqueued
    unsigned int test_id
); // }}}

//! Prints the results of running all tests
void printAllTestResults( // {{{
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
); // }}}

//! Prints the results of running the given tests
void printSelectedTestResults( // {{{
    //! the ids of the tests for which to print results
    std::vector<unsigned int> const& test_ids,
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
); // }}}

//! Prints a message to the user displaying the number of tests that have failed
/*!
If no tests have failed, then it displays a message informing the user that all tests have passed.
*/
void printTestFailureCount( // {{{
    //! the number of tests that failed
    unsigned int number_of_failed_tests,
    //! the color code escape sequences to use when printing the number of failures
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout
); // }}}

//! Print the test tree.
void printTestTree( // {{{
    //! the color code escape sequences to use when printing the test tree
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test tree should be printed
    std::ostream& out=std::cout
); // }}}

//! Runs the test suite using multiple workers and prints the results
void runAllTestsUsingWorkersAndPrintResults( // {{{
    //! The number of worker threads to spawn.
    unsigned int number_of_workers,
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
); // }}}

//! Runs the given tests using multiple workers and prints the results
void runSelectedTestsUsingWorkersAndPrintResults( // {{{
    //! the ids of the tests for which to print results
    std::vector<unsigned int> const& test_ids,
    //! The number of worker threads to spawn.
    unsigned int number_of_workers,
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
); // }}}

//! @}
// }}}

}

#endif
