//@+leo-ver=5-thin
//@+node:gcross.20110601121230.1627: * @file future.hpp
//@@language cplusplus
/*! \file future.hpp
    \brief Type aliases for futures containing test results.
*/

#ifndef ILLUMINATE_FUTURE_HPP
#define ILLUMINATE_FUTURE_HPP

// Includes {{{
//@+<< Includes >>
//@+node:gcross.20110601121230.1629: ** << Includes >>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>

#include "test_tree.hpp"
//@-<< Includes >>
// }}}

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
