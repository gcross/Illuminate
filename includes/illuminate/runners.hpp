//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1623: * @file runners.hpp
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

/*! \file runners.hpp
    \brief Standard test runners supplied by Illuminate.
*/

#ifndef ILLUMINATE_RUNNERS_HPP
#define ILLUMINATE_RUNNERS_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1624: ** << Includes >>
#include <algorithm>
#include <boost/optional.hpp>
#include <iostream>

#include "color_codes.hpp"
#include "future.hpp"
#include "task.hpp"
#include "test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1667: ** Functions
/*! \defgroup TestRunners Runners
    \brief A collection of functions that operate on the global test tree.
    @{
*/
//@+others
//@+node:gcross.20101206161648.1858: *3* enqueueAllTests
//! Populates a test queue and test futures with the tests in a given suite.
void enqueueAllTests(
    //! reference to the output test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the output test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! reference to the input test suite (which defaults to the root)
    Illuminate::Suite const& suite=getRoot()
);
//@+node:gcross.20110813230314.1513: *3* enqueueSelectedTests
//! Populates a test queue and test futures with the tests with the given ids.
void enqueueSelectedTests(
    //! reference to the output test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the output test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! reference to the test ids to be enqueued
    std::vector<unsigned int> const& test_ids
);
//@+node:gcross.20110813230314.1518: *3* enqueueTest
//! Enqueues the test with the given id
void enqueueTest(
    //! reference to the test queue (which in turn is a shared_ptr)
    Illuminate::TestQueue const& queue,
    //! reference to the test futures (which in turn is a shared_ptr)
    Illuminate::TestFutures const& futures,
    //! the id of the test to be enqueued
    unsigned int test_id
);
//@+node:gcross.20110601121230.1633: *3* printAllTestResults
//! Prints the results of running all tests
void printAllTestResults(
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
);
//@+node:gcross.20110813230314.1522: *3* printSelectedTestResults
//! Prints the results of running the given tests
void printSelectedTestResults(
    //! the ids of the tests for which to print results
    std::vector<unsigned int> const& test_ids,
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
);
//@+node:gcross.20110601150226.2634: *3* printTestFailureCount
//! Prints a message to the user displaying the number of tests that have failed
/*!
If no tests have failed, then it displays a message informing the user that all tests have passed.
*/
void printTestFailureCount(
    //! the number of tests that failed
    unsigned int number_of_failed_tests,
    //! the color code escape sequences to use when printing the number of failures
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout
);
//@+node:gcross.20110601121230.1625: *3* printTestTree
//! Print the test tree.
void printTestTree(
    //! the color code escape sequences to use when printing the test tree
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test tree should be printed
    std::ostream& out=std::cout
);
//@+node:gcross.20110601121230.1634: *3* runAllTestsInWorkersAndPrintResults
//! Runs the test suite using multiple workers and prints the results
void runAllTestsUsingWorkersAndPrintResults(
    //! The number of worker threads to spawn.
    unsigned int number_of_workers,
    //! the color code escape sequences to use when printing the test results
    Illuminate::ColorCodes const& color_codes=Illuminate::ColorCodes::ANSI,
    //! the output device to which the test results should be printed
    std::ostream& out=std::cout,
    //! the fetcher to use for obtaining test results
    TestResultFetcher fetchResult=Test::run
);
//@+node:gcross.20110813230314.1524: *3* runSelectedTestsInWorkersAndPrintResults
//! Runs the given tests using multiple workers and prints the results
void runSelectedTestsUsingWorkersAndPrintResults(
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
);
//@-others

//! @}
//@-others

}

#endif
//@-leo
