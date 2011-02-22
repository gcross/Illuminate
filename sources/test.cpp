//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1418: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1419: ** << Includes >>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/any.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>
#include <sstream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1420: ** << Usings >>
using namespace boost;
using namespace boost::program_options;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101205182001.1421: ** class Test
//@+node:gcross.20101205182001.1422: *3* (constructors)
Test::Test(const string& name, Suite& parent, function<void ()> runner)
    : Node(name,&parent)
    , id(getRoot().registerTest(this))
    , runner(runner)
{
    parent.tests.push_back(this);
}
//@+node:gcross.20101206161648.1515: *3* (exceptions)
const char* Test::FailuresAccessedOutsideTestContext::what() const throw() {
    return "an attempt has been made to register a failure outside of a test context";
}
//@+node:gcross.20101206142257.1467: *3* (static fields)
thread_specific_ptr<vector<string> > Test::current_failures;
enum FatalityMode Test::fatality_mode = NONE_FATAL;
//@+node:gcross.20101206161648.1525: *3* annotateFailureMessage
string Test::annotateFailureMessage(const char* filename, int line_number, const string& message) {
    stringstream annotated_message;
    annotated_message << filename << ':' << line_number << " - " << message;
    return annotated_message.str();
}
//@+node:gcross.20101206161648.1517: *3* die
void Test::die() {
    throw FatalTestFailure();
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
    if(fatality_mode >= EXCEPTIONS_FATAL) {
        runner();
    } else {
        try {
            runner();
        } catch(FatalTestFailure) {
            // Nothing to do in this case.
        } catch(std::exception& e) {
            registerFailure("Exception thrown: " + string(e.what()));
        } catch(...) {
            registerFailure("Unknown exception type thrown");
        }
    }
    TestResult failures(current_failures.get());
    current_failures.release();
    return failures;
}
//@+node:gcross.20101206161648.1513: *3* registerFailure
void Test::registerFailure(const string& message, bool const fatal) {
    if(fatality_mode >= ALL_FATAL) {
        throw FatalError(message);
    }
    getFailures().push_back(message);
    if(fatal) die();
}
//@+node:gcross.20101206161648.1527: *3* registerFailure
void Test::registerFailure(const char* filename, unsigned int const line_number, const string& message, bool const fatal) {
    registerFailure(annotateFailureMessage(filename,line_number,message),fatal);
}
//@+node:gcross.20110204202041.1556: ** function validate
void validate(any& v,
              const vector<std::string>& values,
              FatalityMode* target_type, int)
{
    // Make sure no previous assignment to 'a' was made.
    validators::check_first_occurrence(v);

    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    string s = validators::get_single_string(values);
    to_lower(s);

    static string const none("none"), exceptions("exceptions"), all("all");
    if(equals(s,none)) {
        v = any(NONE_FATAL);
    } else if(equals(s,exceptions)) {
        v = any(EXCEPTIONS_FATAL);
    } else if(equals(s,all)) {
        v = any(ALL_FATAL);
    } else {
        throw invalid_option_value(s);
    }
}
//@-others

}
//@-leo
