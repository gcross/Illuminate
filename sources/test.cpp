//@+leo-ver=5-thin
//@+node:gcross.20101205182001.1418: * @thin test.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101205182001.1419: ** << Includes >>
#include <sstream>

#include "illuminate/core.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101205182001.1420: ** << Usings >>
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
const char* Test::FailureRegisteredOutsideTestContext::what() const throw() {
    return "an attempt has been made to register a failure outside of a test context";
}
//@+node:gcross.20101206142257.1467: *3* (static fields)
thread_specific_ptr<vector<string> > Test::current_failures;
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
//@+node:gcross.20101206142257.1395: *3* operator()
TestResult Test::operator()() const {
    current_failures.reset(new vector<string>());
    try {
        runner();
    } catch(FatalTestFailure) {
        // Nothing to do in this case.
    } catch(std::exception& e) {
        registerFailure("Exception thrown: " + string(e.what()));
    } catch(...) {
        registerFailure("Unknown exception type thrown");
    }
    TestResult failures(current_failures.get());
    current_failures.release();
    return failures;
}
//@+node:gcross.20101206161648.1513: *3* registerFailure
void Test::registerFailure(const string& message) {
    vector<string>* failures = current_failures.get();
    if(failures == NULL) {
        throw FailureRegisteredOutsideTestContext();
    }
    failures->push_back(message);
}
//@+node:gcross.20101206161648.1527: *3* registerFailure
void Test::registerFailure(const char* filename, int line_number, const string& message) {
    registerFailure(annotateFailureMessage(filename,line_number,message));
}
//@+node:gcross.20101206161648.1531: *3* registerFatalFailure
void Test::registerFatalFailure(const string& message) {
    registerFailure(message);
    die();
}
//@+node:gcross.20101206161648.1533: *3* registerFatalFailure
void Test::registerFatalFailure(const char* filename, int line_number, const string& message) {
    registerFatalFailure(annotateFailureMessage(filename,line_number,message));
}
//@-others

}
//@-leo
