//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1623: * @thin runners.hpp
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

#ifndef ILLUMINATE_RUNNERS_HPP
#define ILLUMINATE_RUNNERS_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1624: ** << Includes >>
#include <algorithm>
#include <boost/optional.hpp>
#include <iostream>

#include "illuminate/core.hpp"
#include "illuminate/color_codes.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1667: ** Functions
void printTestList(ColorCodes const& color_codes=ColorCodes::ANSI, std::ostream& out=std::cout);
void printTestFutures(TestFutures const& futures, ColorCodes const& color_codes=ColorCodes::ANSI, std::ostream& out=std::cout);
void runTestsAndPrintResults(ColorCodes const& color_codes=ColorCodes::ANSI, std::ostream& out=std::cout);
void runTestsInThreadsAndPrintResults(boost::optional<unsigned int> const requested_number_of_workers=boost::none, ColorCodes const& color_codes=ColorCodes::ANSI, std::ostream& out=std::cout);
//@-others

}

#endif
//@-leo
