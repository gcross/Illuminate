//@+leo-ver=5-thin
//@+node:gcross.20101206142257.1399: * @thin macros.hpp
//@@language cplusplus

#ifndef ILLUMINATE_MACROS_HPP
#define ILLUMINATE_MACROS_HPP

//@+others
//@+node:gcross.20101206142257.1405: ** Test declaration
//@+node:gcross.20101206142257.1406: *3* testSuite
#define testSuite(suiteName) \
    namespace SUITE_##suiteName { \
        static Illuminate::Suite& _getParentSuite() { \
            static Illuminate::Suite& suite = getParentSuite().lookupSuite(Illuminate::underscoresToSpaces(#suiteName)); \
            return suite; \
        } \
        static Illuminate::Suite& getParentSuite() { return _getParentSuite(); } \
    } \
    namespace SUITE_##suiteName
//@+node:gcross.20101206142257.1407: *3* testCase
#define testCase(caseName) \
    static void TEST_CASE_RUNNER_##caseName(); \
    static Illuminate::Test TEST_CASE_##caseName(#caseName,getParentSuite(),TEST_CASE_RUNNER_##caseName); \
    static void TEST_CASE_RUNNER_##caseName()
//@+node:gcross.20101206161648.1519: ** Checks
//@+node:gcross.20101206161648.1535: *3* check
#define check(expression) { \
    if(not (expression)) { \
        Illuminate::Test::registerFailure(__FILE__,__LINE__,"Assertion failed: " #expression); \
    } \
}
//@+node:gcross.20101206161648.1520: ** Assertions
//@+node:gcross.20101206161648.1522: *3* assert_
#define assert_(expression) { \
    if(not (expression)) { \
        Illuminate::Test::registerFatalFailure(__FILE__,__LINE__,"Assertion failed: " #expression); \
    } \
}
//@+node:gcross.20101206161648.1598: ** Failures
//@+node:gcross.20101206161648.1599: *3* fail
#define fail(message) Illuminate::Test::registerFailure(message)
//@+node:gcross.20101206161648.1601: *3* fatallyFail
#define fatallyFail(message) Illuminate::Test::registerFatalFailure(message)
//@-others

#endif
//@-leo
