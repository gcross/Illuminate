//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1306: * @file suite.cpp
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
//@+node:gcross.20101205182001.1307: ** << Includes >>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/sort.hpp>

#include "illuminate/test_tree.hpp"
#include "illuminate/visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1314: ** << Usings >>
using boost::adaptors::indirected;
using boost::format;
namespace lambda = boost::lambda;
using boost::optional;

using std::string;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1308: ** struct Suite
//@+node:gcross.20101205182001.1313: *3* (constructors)
Suite::Suite(string const& name, optional<Suite const&> const parent, optional<bool> const skipped)
    : Node(name,parent,skipped)
{ }
//@+node:gcross.20110809112154.2074: *3* constructPath
boost::format Suite::constructPath() const {
    return format("%1%/") % name;
}
//@+node:gcross.20101205182001.1319: *3* lookupSuite
Suite& Suite::lookupSuite(string const& name,optional<bool> const skipped) {
    std::vector<Suite*>::iterator iter =
        boost::find_if(nested_suites,lambda::bind(&Suite::name,lambda::_1) == name);
    if(iter != nested_suites.end()) {
        return **iter;
    } else {
        Suite* suite = new Suite(name,*this,skipped);
        nested_suites.push_back(suite);
        return *suite;
    }
}
//@+node:gcross.20101205182001.1316: *3* visit
void Suite::visit(Visitor& visitor) const {
    visitor.enter(*this);
    BOOST_FOREACH(const Suite& suite, nested_suites | indirected) { suite.visit(visitor); }
    BOOST_FOREACH(const Test& test, tests | indirected) { visitor.test(test); }
    visitor.exit(*this);
}
//@+node:gcross.20110813135646.1508: *3* sort
void Suite::sort() {
    boost::sort(nested_suites, lambda::bind(&Suite::name,lambda::_1) < lambda::bind(&Suite::name,lambda::_2));
    boost::sort(tests, lambda::bind(&Test::name,lambda::_1) < lambda::bind(&Test::name,lambda::_2));
    boost::for_each(nested_suites, lambda::bind(&Suite::sort,lambda::_1));
}
//@-others

}

//@+<< Outside Namespace >>
//@+node:gcross.20101205214942.2497: ** << Outside Namespace >>
//@+others
//@+node:gcross.20101205214942.2499: *3* getParentSuite
Illuminate::Suite& getParentSuite() { return Illuminate::getRoot(); }
//@-others
//@-<< Outside Namespace >>
//@-leo
