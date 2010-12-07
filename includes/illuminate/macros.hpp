//@+leo-ver=5-thin
//@+node:gcross.20101206142257.1399: * @thin macros.hpp
//@@language cplusplus

#ifndef ILLUMINATE_MACROS_HPP
#define ILLUMINATE_MACROS_HPP

//@+others
//@+node:gcross.20101206142257.1405: ** Test declarations
//@+node:gcross.20101206142257.1406: *3* TEST_SUITE
#define TEST_SUITE(suiteName) \
    namespace SUITE_##suiteName { \
        static Illuminate::Suite& _getParentSuite() { \
            static Illuminate::Suite& suite = getParentSuite().lookupSuite(Illuminate::underscoresToSpaces(#suiteName)); \
            return suite; \
        } \
        static Illuminate::Suite& getParentSuite() { return _getParentSuite(); } \
    } \
    namespace SUITE_##suiteName
//@+node:gcross.20101206142257.1407: *3* TEST_CASE
#define TEST_CASE(caseName) \
    static void TEST_CASE_RUNNER_##caseName(); \
    static Illuminate::Test TEST_CASE_##caseName(#caseName,getParentSuite(),TEST_CASE_RUNNER_##caseName); \
    static void TEST_CASE_RUNNER_##caseName()
//@+node:gcross.20101206161648.1614: ** Helpers
//@+node:gcross.20101206161648.1620: *3* DO_CHECK_WITH_X_ARGUMENT
#define DO_CHECK_WITH_1_ARGUMENT(F,A,K) TEST_##K(F##_EXPRESSION(A),F##_MESSAGE(A))
#define DO_CHECK_WITH_2_ARGUMENTS(F,A,B,K) TEST_##K(F##_EXPRESSION(A,B),F##_MESSAGE(A,B))
#define DO_CHECK_WITH_3_ARGUMENTS(F,A,B,C,K) TEST_##K(F##_EXPRESSION(A,B,C),F##_MESSAGE(A,B,C))
//@+node:gcross.20101206161648.1615: *3* TEST_ASSERTION
#define TEST_ASSERTION(expression,message) { if(not (expression)) { Illuminate::Test::registerFatalFailure(__FILE__,__LINE__,message); } }
//@+node:gcross.20101206161648.1617: *3* TEST_EXPECTATION
#define TEST_EXPECTATION(expression,message) { if(not (expression)) { Illuminate::Test::registerFailure(__FILE__,__LINE__,(message)); } }
//@+node:gcross.20101206161648.1520: ** Checks
//@+node:gcross.20101206161648.1618: *3* EQ_
#define EQ_EXPRESSION(expected_value,actual_value) (expected_value) == (actual_value)
#define EQ_MESSAGE(expected_value,actual_value) "Actual value <" #actual_value "> does not match the expected value <" #expected_value ">"
#define ASSERT_EQ(expected_value,actual_value) DO_CHECK_WITH_2_ARGUMENTS(EQ,expected_value,actual_value,ASSERTION)
#define EXPECT_EQ(expected_value,actual_value) DO_CHECK_WITH_2_ARGUMENTS(EQ,expected_value,actual_value,EXPECTATION)
//@+node:gcross.20101206161648.1622: *3* TRUE_
#define TRUE_EXPRESSION(expression) expression
#define TRUE_MESSAGE(expression) "Assertion failed: " #expression
#define ASSERT_TRUE(expression) DO_CHECK_WITH_1_ARGUMENT(TRUE,expression,ASSERTION)
#define EXPECT_TRUE(expression) DO_CHECK_WITH_1_ARGUMENT(TRUE,expression,EXPECTATION)
//@+node:gcross.20101206161648.1598: ** Failures
//@+node:gcross.20101206161648.1599: *3* FAIL
#define FAIL(message) Illuminate::Test::registerFailure(message)
//@+node:gcross.20101206161648.1601: *3* FATALLY_FAIL
#define FATALLY_FAIL(message) Illuminate::Test::registerFatalFailure(message)
//@-others

#endif
//@-leo
