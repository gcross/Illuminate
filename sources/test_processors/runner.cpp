//@+leo-ver=5-thin
//@+node:gcross.20110203233241.1615: * @file runner.cpp
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

//@+<< Includes >>
//@+node:gcross.20110203233241.1616: ** << Includes >>
#include "illuminate/test_processors/runner.hpp"
#include "illuminate/test_result_callback.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20110203233241.1617: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20110203233241.1618: ** class RunnerTestProcessor
//@+node:gcross.20110203233241.1625: *3* (constructors)
RunnerTestProcessor::RunnerTestProcessor() : number_of_failed_tests(0) {}
//@+node:gcross.20110203233241.1621: *3* operator()
void RunnerTestProcessor::operator()(Test const& test, TestResultCallback& callback) {
    if(test.skipped) {
        callback.testSkipped(test);
    } else {
        callback.testStarted(test);
        TestResult result = test();
        if(result->size() == 0) {
            callback.testPassed(test);
        } else {
            ++number_of_failed_tests;
            callback.testFailed(test,*result);
        }
    }
}
//@-others

}
//@-leo