//@+leo-ver=5-thin
//@+node:gcross.20110601121230.1630: * @file task.hpp
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

/*! \file task.hpp
    \brief Type aliases for tasks that run tests.
*/

#ifndef ILLUMINATE_TASK_HPP
#define ILLUMINATE_TASK_HPP

//@+<< Includes >>
//@+node:gcross.20110601121230.1631: ** << Includes >>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110601121230.1632: ** Type aliases
//! A task that runs a test to obtain its result.
typedef boost::shared_ptr<boost::packaged_task<TestResult> > TestTask;

//! A queue of test tasks.
typedef boost::shared_ptr<std::queue<TestTask> > TestQueue;
//@-others

}

#endif
//@-leo