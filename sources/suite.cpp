// Includes {{{
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/sort.hpp>

#include "illuminate/test_tree.hpp"
#include "illuminate/visitor.hpp"
// }}}

// Usings {{{
using boost::adaptors::indirected;
using boost::format;
namespace lambda = boost::lambda;
using boost::optional;

using std::string;
// }}}

namespace Illuminate {

// struct Suite {{{
Suite::Suite(string const& name, optional<Suite const&> const parent, optional<bool> const skipped) // {{{
    : Node(name,parent,skipped)
{ } // }}}
boost::format Suite::constructPath() const { // {{{
    return format("%1%/") % name;
} // }}}
Suite& Suite::lookupSuite(string const& name,optional<bool> const skipped) { // {{{
    std::vector<Suite*>::iterator iter =
        boost::find_if(nested_suites,lambda::bind(&Suite::name,lambda::_1) == name);
    if(iter != nested_suites.end()) {
        return **iter;
    } else {
        Suite* suite = new Suite(name,*this,skipped);
        nested_suites.push_back(suite);
        return *suite;
    }
} // }}}
void Suite::visit(Visitor& visitor) const { // {{{
    visitor.enter(*this);
    BOOST_FOREACH(const Suite& suite, nested_suites | indirected) { suite.visit(visitor); }
    BOOST_FOREACH(const Test& test, tests | indirected) { visitor.test(test); }
    visitor.exit(*this);
} // }}}
void Suite::sort() { // {{{
    boost::sort(nested_suites, lambda::bind(&Suite::name,lambda::_1) < lambda::bind(&Suite::name,lambda::_2));
    boost::sort(tests, lambda::bind(&Test::name,lambda::_1) < lambda::bind(&Test::name,lambda::_2));
    boost::for_each(nested_suites, lambda::bind(&Suite::sort,lambda::_1));
} // }}}
// }}}

}

// Outside namespace {{{
Illuminate::Suite& getParentSuite() { return Illuminate::getRoot(); }
// }}}
