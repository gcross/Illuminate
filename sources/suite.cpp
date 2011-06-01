//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1306: * @thin suite.cpp
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

#include "illuminate/test_tree.hpp"
#include "illuminate/visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1314: ** << Usings >>
using boost::optional;

using std::string;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1308: ** struct Suite
//@+node:gcross.20101205182001.1313: *3* (constructors)
Suite::Suite(string const& name, optional<Suite const&> const parent, optional<bool> const skipped)
    : Node(name,parent,skipped)
{ }
//@+node:gcross.20101205182001.1319: *3* lookupSuite
Suite& Suite::lookupSuite(string const& name,optional<bool> const skipped) {
    BOOST_FOREACH(Suite& suite, nested_suites) {
        if(suite.name == name) { return suite; }
    }
    nested_suites.push_back(Suite(name,*this,skipped));
    return *(--nested_suites.end());
}
//@+node:gcross.20101205182001.1316: *3* visit
void Suite::visit(Visitor& visitor) const {
    visitor.enter(*this);
    BOOST_FOREACH(const Suite& suite, nested_suites) {
        suite.visit(visitor);
    }
    BOOST_FOREACH(const Test* test, tests) {
        visitor.test(*test);
    }
    visitor.exit(*this);
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
