//@+leo-ver=5-thin
//@+node:gcross.20110601121230.1627: * @file future.hpp
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
    \brief Type aliases for futures containing test results.
*/

#ifndef ILLUMINATE_FUTURE_HPP
#define ILLUMINATE_FUTURE_HPP

//@+<< Includes >>
//@+node:gcross.20110601121230.1629: ** << Includes >>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

#include "test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110601121230.1628: ** Type aliases
//! A future with a test result
typedef boost::shared_ptr<boost::unique_future<TestResult> > TestFuture;

//! A mapping from tests to futures with their results
/*!
\note This scheme works because tests are assigned sequential unique identifiers from a global pool as they are created.
*/
typedef boost::shared_ptr<boost::unordered_map<unsigned int,TestFuture> > TestFutures;
//@-others

}

#endif
//@-leo
