//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1573: * @file future.hpp
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

/*! \file future.hpp
    \brief Illuminate::FutureTestResultFetcher class
*/

#ifndef ILLUMINATE_TEST_RESULT_FETCHERS_FUTURE_HPP
#define ILLUMINATE_TEST_RESULT_FETCHERS_FUTURE_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1574: ** << Includes >>
#include "../future.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1577: ** struct FutureTestResultFetcher
//! A test result fetcher that fetching the result from a provided future.
struct FutureTestResultFetcher {
    //! Futures providing the test results.
    TestFutures futures;

    //! Constructor
    /*! \param futures futures providing the test results */
    FutureTestResultFetcher(TestFutures const& futures);

    //! Fetches the result of the given test
    TestResult operator()(unsigned int test_id) const;
};
//@-others

}

#endif
//@-leo
