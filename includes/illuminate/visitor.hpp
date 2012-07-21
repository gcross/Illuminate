/*! \file visitor.hpp
    \brief Illuminate::Visitor class
*/

#ifndef ILLUMINATE_VISITOR_HPP
#define ILLUMINATE_VISITOR_HPP

// Includes {{{
#include "test_tree.hpp"
// }}}

namespace Illuminate {

//! Test tree visitor.
struct Visitor { // {{{
    //! Called when a suite has been entered.
    virtual void enter(Suite const& suite) = 0;
    //! Called when a suite has been exited.
    virtual void exit(Suite const& suite) = 0;
    //! Called to visit a test.
    virtual void test(Test const& test) = 0;
}; // }}}

}

#endif
