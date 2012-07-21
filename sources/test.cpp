// Includes {{{
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/any.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <sstream>

#include "illuminate/test_tree.hpp"
// }}}

// Usings {{{
using boost::any;
using boost::equals;
using boost::format;
using boost::function;
using boost::optional;
using boost::program_options::invalid_option_value;
namespace validators = boost::program_options::validators;
using boost::thread_specific_ptr;
using boost::to_lower;

using std::string;
using std::stringstream;
using std::vector;
// }}}

namespace Illuminate {

// class Test {{{
// static fields {{{
thread_specific_ptr<vector<string> > Test::current_failures;
enum AbortMode Test::abort_mode = NEVER_ABORT;
// }}}

Test::Test(string const& name, Suite& parent, function<void ()> const runner, optional<bool> const skipped) // {{{
    : Node(name,parent,skipped)
    , id(getRoot().registerTest(this))
    , runner(runner)
{
    parent.tests.push_back(this);
} // }}}
char const* Test::FailuresAccessedOutsideTestContext::what() const throw() { // {{{
    return "an attempt has been made to register a failure outside of a test context";
} // }}}
string Test::annotateFailureMessage(char const* filename, int const line_number, string const& message) { // {{{
    stringstream annotated_message;
    annotated_message << filename << ':' << line_number << " - " << message;
    return annotated_message.str();
} // }}}
boost::format Test::constructPath() const { // {{{
    return format("%1%%2%") % parent->constructPath() % name;
} // }}}
unsigned int Test::countFailures() { // {{{
    return getFailures().size();
} // }}}
void Test::die() { // {{{
    throw FatalTestFailure();
} // }}}
void Test::eraseFailuresAfter(unsigned int const number_of_failures) { // {{{
    vector<string>& failures = getFailures();
    if(number_of_failures < failures.size()) {
        failures.erase(failures.begin()+number_of_failures,failures.end());
    }
} // }}}
vector<string>& Test::getFailures() { // {{{
    vector<string>* failures = current_failures.get();
    if(failures == NULL) {
        throw FailuresAccessedOutsideTestContext();
    }
    return *failures;
} // }}}
TestResult Test::operator()() const { // {{{
    current_failures.reset(new vector<string>());
    if(abort_mode >= ABORT_ON_EXCEPTION) {
        runner();
    } else {
        try {
            runner();
        } catch(FatalTestFailure) {
            // Nothing to do in this case.
        } catch(std::exception const& e) {
            registerFailure("Exception thrown: " + string(e.what()));
        } catch(std::exception* e) { // in case exception is thrown by pointer.
            registerFailure("Exception thrown: " + string(e->what()));
            delete e;
        } catch(...) {
            registerFailure("Unknown exception type thrown");
        }
    }
    TestResult failures(current_failures.get());
    current_failures.release();
    return failures;
} // }}}
void Test::registerFailure(string const& message, bool const fatal) { // {{{
    if(abort_mode >= ABORT_ON_ANY_FAILURE) {
        throw FatalError(message);
    }
    getFailures().push_back(message);
    if(fatal) die();
} // }}}
void Test::registerFailure(char const* filename, unsigned int const line_number, string const& message, bool const fatal) { // {{{
    registerFailure(annotateFailureMessage(filename,line_number,message),fatal);
} // }}}
TestResult Test::run(unsigned int test_id) { // {{{
    return getRoot().lookupTest(test_id)();
} // }}}
// }}}

// Functions {{{

void validate(any& v
             ,vector<std::string> const& values
             ,AbortMode* target_type
             ,int const
             )
{ // {{{
    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);

    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    string s = validators::get_single_string(values);
    to_lower(s);

    static string const none("none"), exceptions("exceptions"), all("all");
    if(equals(s,none)) {
        v = any(NEVER_ABORT);
    } else if(equals(s,exceptions)) {
        v = any(ABORT_ON_EXCEPTION);
    } else if(equals(s,all)) {
        v = any(ABORT_ON_ANY_FAILURE);
    } else {
        throw invalid_option_value(s);
    }
} // }}}

// }}}

}
