//@+leo-ver=5-thin
//@+node:gcross.20101206104532.1395: * @file root.cpp
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
//@+node:gcross.20101206104532.1396: ** << Includes >>
#include "illuminate/test_tree.hpp"
#include "illuminate/visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206104532.1397: ** << Usings >>
using boost::format;
using boost::none;

using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206104532.1398: ** class Root
//@+node:gcross.20101206104532.1399: *3* (constructors)
Root::Root() : Suite("Root",none) { }
//@+node:gcross.20110809112154.2049: *3* lookupTest
Test const& Root::lookupTest(unsigned int id) const {
    return *tests[id];
}
//@+node:gcross.20101206104532.1401: *3* registerTest
unsigned int Root::registerTest(Test* const test) {
    unsigned int const test_id = tests.size();
    tests.push_back(test);
    return test_id;
}
//@+node:gcross.20110809112154.2410: *3* numberOfTests
unsigned int Root::numberOfTests() const {
    return tests.size();
}
//@+node:gcross.20110813135646.1512: *3* sort
void Root::sort() {
    Suite::sort();
    struct RenumberVisitor : public Visitor {
        vector<Test*>& tests;
        unsigned int current_test_id;
        RenumberVisitor(vector<Test*>& tests)
          : tests(tests)
          , current_test_id(0)
        {}
        virtual void enter(Suite const& suite) {}
        virtual void exit(Suite const& suite) {}
        virtual void test(Test const& test) {
            Test& const_overridden_test = const_cast<Test&>(test);
            const_overridden_test.id = current_test_id;
            tests[current_test_id] = &const_overridden_test;
            ++current_test_id;
        }
    } visitor(tests);
    visit(visitor);
}
//@+node:gcross.20101206104532.1406: ** getRoot
Root& getRoot() {
    static Root root;
    return root;
}
//@-others

}
//@-leo
