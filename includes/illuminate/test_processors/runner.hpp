//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1602: * @file runner.hpp
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

/*! \file runner.hpp
    \brief Illuminate::RunnerTestProcessor class
*/

#ifndef ILLUMINATE_TEST_PROCESSORS_RUNNER_HPP
#define ILLUMINATE_TEST_PROCESSORS_RUNNER_HPP

//@+<< Includes >>
//@+node:gcross.20110203233241.1603: ** << Includes >>
#include "../test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110203233241.1605: ** class RunnerTestProcessor
//! A test processor that processes a test by simply running the body of the test in the current thread.
struct RunnerTestProcessor {
    //! A counter that tracks the number of tests that have failed.
    unsigned int number_of_failed_tests;

    RunnerTestProcessor();

    //! Process the test
    void operator()(
        //! test to be processed
        Test const& test,
        //! callback to be notified
        TestResultCallback& callback
    );
};
//@-others

}

#endif
//@-leo