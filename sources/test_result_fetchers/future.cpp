//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1587: * @file future.cpp
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
//@+node:gcross.20101208142631.1588: ** << Includes >>
#include "illuminate/test_result_fetchers/future.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101208142631.1589: ** << Usings >>
//@-<< Usings >>

//@+others
//@+node:gcross.20101208142631.1590: ** class FutureTestResultFetcher
//@+node:gcross.20101208142631.1591: *3* (constructors)
FutureTestResultFetcher::FutureTestResultFetcher(TestFutures const& futures)
    : futures(futures)
{ }
//@+node:gcross.20101208142631.1593: *3* operator()
TestResult FutureTestResultFetcher::operator()(Test const& test) const {
    return (*futures)[test.id]->get();
}
//@-others

}
//@-leo
