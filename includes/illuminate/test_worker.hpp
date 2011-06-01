//@+leo-ver=5-thin
//@+node:gcross.20101208142631.1499: * @thin test_worker.hpp
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

#ifndef ILLUMINATE_TEST_WORKER_HPP
#define ILLUMINATE_TEST_WORKER_HPP

//@+<< Includes >>
//@+node:gcross.20101208142631.1500: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101208142631.1502: ** class TestWorker
class TestWorker {
public:
    TestWorker(TestQueue const& queue,boost::shared_ptr<boost::mutex> const& queue_mutex, boost::shared_ptr<const bool> const& stop_signal);
    void operator()();
protected:
    TestQueue queue;
    boost::shared_ptr<boost::mutex> queue_mutex;
    boost::shared_ptr<const bool> stop_signal;
};
//@-others

}

#endif
//@-leo
