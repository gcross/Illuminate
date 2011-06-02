//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1418: * @file test.cpp
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
//@+node:gcross.20101205182001.1419: ** << Includes >>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/any.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <sstream>

#include "illuminate/test_tree.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1420: ** << Usings >>
using boost::any;
using boost::equals;
using boost::function;
using boost::optional;
using boost::program_options::invalid_option_value;
namespace validators = boost::program_options::validators;
using boost::thread_specific_ptr;
using boost::to_lower;

using std::string;
using std::stringstream;
using std::vector;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1421: ** class Test
//@+node:gcross.20101205182001.1422: *3* (constructors)
Test::Test(string const& name, Suite& parent, function<void ()> const runner, optional<bool> const skipped)
    : Node(name,parent,skipped)
    , id(getRoot().registerTest(this))
    , runner(runner)
{
    parent.tests.push_back(this);
}
//@+node:gcross.20101206161648.1515: *3* (exceptions)
char const* Test::FailuresAccessedOutsideTestContext::what() const throw() {
    return "an attempt has been made to register a failure outside of a test context";
}
//@+node:gcross.20101206142257.1467: *3* (static fields)
thread_specific_ptr<vector<string> > Test::current_failures;
enum AbortMode Test::abort_mode = NEVER_ABORT;
//@+node:gcross.20101206161648.1525: *3* annotateFailureMessage
string Test::annotateFailureMessage(char const* filename, int const line_number, string const& message) {
    stringstream annotated_message;
    annotated_message << filename << ':' << line_number << " - " << message;
    return annotated_message.str();
}
//@+node:gcross.20110222132831.1570: *3* countFailures
unsigned int Test::countFailures() {
    return getFailures().size();
}
//@+node:gcross.20101206161648.1517: *3* die
void Test::die() {
    throw FatalTestFailure();
}
//@+node:gcross.20110222160854.1885: *3* eraseFailuresAfter
void Test::eraseFailuresAfter(unsigned int const number_of_failures) {
    vector<string>& failures = getFailures();
    if(number_of_failures < failures.size()) {
        failures.erase(failures.begin()+number_of_failures,failures.end());
    }
}
//@+node:gcross.20110222132831.1568: *3* getFailures
vector<string>& Test::getFailures() {
    vector<string>* failures = current_failures.get();
    if(failures == NULL) {
        throw FailuresAccessedOutsideTestContext();
    }
    return *failures;
}
//@+node:gcross.20101206142257.1395: *3* operator()
TestResult Test::operator()() const {
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
}
//@+node:gcross.20101206161648.1513: *3* registerFailure
void Test::registerFailure(string const& message, bool const fatal) {
    if(abort_mode >= ABORT_ON_ANY_FAILURE) {
        throw FatalError(message);
    }
    getFailures().push_back(message);
    if(fatal) die();
}
//@+node:gcross.20101206161648.1527: *3* registerFailure
void Test::registerFailure(char const* filename, unsigned int const line_number, string const& message, bool const fatal) {
    registerFailure(annotateFailureMessage(filename,line_number,message),fatal);
}
//@+node:gcross.20110601150226.2637: *3* runAndReturnResult
TestResult Test::run(Test const& test) {
    return test();
}
//@+node:gcross.20110204202041.1556: ** function validate
void validate(any& v
             ,vector<std::string> const& values
             ,AbortMode* target_type
             ,int const
             )
{
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
}
//@-others

}
//@-leo
