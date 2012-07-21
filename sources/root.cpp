// Includes {{{
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range/algorithm/remove_copy_if.hpp>
#include <iterator>

#include "illuminate/test_tree.hpp"
#include "illuminate/visitor.hpp"
// }}}

// Usings {{{
using boost::format;
namespace lambda = boost::lambda;
using boost::none;
using boost::remove_copy_if;

using std::back_inserter;
using std::cerr;
using std::endl;
using std::vector;
// }}}

namespace Illuminate {

// class Root {{{
Root::Root() : Suite("Root",none) { }
void Root::checkTestIds(vector<unsigned int> const& test_ids) const { // {{{
    vector<unsigned int> bad_test_ids;
    remove_copy_if(test_ids,back_inserter(bad_test_ids),lambda::_1 < numberOfTests());
    switch(bad_test_ids.size()) {
        case 0: return;
        case 1:
            cerr << "Bad test id: " << bad_test_ids[0] << endl;
            exit(-1);
        default:
            cerr << "Bad test ids:" << endl;
            BOOST_FOREACH(unsigned int const bad_test_id, bad_test_ids) {
                cerr << "    " << bad_test_id << endl;
            }
            exit(-1);
    }
} // }}}
Test const& Root::lookupTest(unsigned int id) const { // {{{
    return *tests[id];
} // }}}
unsigned int Root::numberOfTests() const { // {{{
    return tests.size();
} // }}}
unsigned int Root::registerTest(Test* const test) { // {{{
    unsigned int const test_id = tests.size();
    tests.push_back(test);
    return test_id;
} // }}}
void Root::sort() { // {{{
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
} // }}}
// }}}

// Functions {{{

Root& getRoot() {
    static Root root;
    return root;
}

// }}}

}
