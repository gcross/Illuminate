/*! \file task.hpp
    \brief Type aliases for tasks that run tests.
*/

#ifndef ILLUMINATE_TASK_HPP
#define ILLUMINATE_TASK_HPP

// Includes {{{
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "test_tree.hpp"
// }}}

namespace Illuminate {

// Type aliases {{{

//! A task that runs a test to obtain its result.
typedef std::pair<unsigned int, boost::shared_ptr<boost::promise<TestResult> > > TestTask;

//! A queue of test tasks.
typedef boost::shared_ptr<std::queue<TestTask> > TestQueue;

// }}}

}

#endif
