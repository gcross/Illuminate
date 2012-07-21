/*! \file future.hpp
    \brief Illuminate::FutureTestResultFetcher class
*/

#ifndef ILLUMINATE_TEST_RESULT_FETCHERS_FUTURE_HPP
#define ILLUMINATE_TEST_RESULT_FETCHERS_FUTURE_HPP

// Includes {{{
#include "../future.hpp"
// }}}

namespace Illuminate {

//! A test result fetcher that fetching the result from a provided future.
struct FutureTestResultFetcher { // {{{
    //! Futures providing the test results.
    TestFutures futures;

    //! Constructor
    /*! \param futures futures providing the test results */
    FutureTestResultFetcher(TestFutures const& futures);

    //! Fetches the result of the given test
    TestResult operator()(unsigned int test_id) const;
}; // }}}

}

#endif
