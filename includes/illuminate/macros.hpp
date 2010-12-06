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
//@-others

#endif
//@-leo
