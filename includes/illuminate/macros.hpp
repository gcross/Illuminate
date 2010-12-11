//@+leo-ver=5-thin
//@+node:gcross.20101206142257.1399: * @thin macros.hpp
//@@language cplusplus

#ifndef ILLUMINATE_MACROS_HPP
#define ILLUMINATE_MACROS_HPP

//@+<< Includes >>
//@+node:gcross.20101209013121.1492: ** << Includes >>
#include <boost/format.hpp>
//@-<< Includes >>

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
    static Illuminate::Test TEST_CASE_##caseName(Illuminate::underscoresToSpaces(#caseName),getParentSuite(),TEST_CASE_RUNNER_##caseName); \
    static void TEST_CASE_RUNNER_##caseName()
//@+node:gcross.20101206161648.1614: ** Helpers
//@+node:gcross.20101206161648.1620: *3* DEFINE_CHECK_WITH_X_ARGUMENTS
#define DEFINE_CHECK_WITH_1_ARGUMENTS(K,F) \
    namespace Illuminate {\
        template<class T1> void DO_##F##_##K(const char* filename, int line_number, const T1& a) {\
            DO_TEST_##K(filename,line_number,F##_EXPRESSION(a),F##_MESSAGE(a));\
        }\
    }
#define DEFINE_CHECK_WITH_2_ARGUMENTS(K,F) \
    namespace Illuminate {\
        template<class T1,class T2> void DO_##F##_##K(const char* filename, int line_number, const T1& a, const T2& b) {\
            DO_TEST_##K(filename,line_number,F##_EXPRESSION(a,b),F##_MESSAGE(a,b));\
        }\
    }
#define DEFINE_CHECK_WITH_3_ARGUMENTS(K,F) \
    namespace Illuminate {\
        template<class T1,class T2,class T3> void DO_##F##_##K(const char* filename, int line_number, const T1& a, const T2& b, const T3& c) {\
            DO_TEST_##K(filename,line_number,F##_EXPRESSION(a,b,c),F##_MESSAGE(a,b,c));\
        }\
    }
//@+node:gcross.20101209224839.2292: *3* DEFINE_CHECKS
#define DEFINE_CHECKS(F,N) \
    DEFINE_CHECK_WITH_##N##_ARGUMENTS(ASSERT,F) \
    DEFINE_CHECK_WITH_##N##_ARGUMENTS(EXPECT,F)
//@+node:gcross.20101209224839.2290: *3* DO_CHECK_WITH_X_ARGUMENTS
#define DO_CHECK_WITH_1_ARGUMENTS(K,F,A) Illuminate::DO_##F##_##K(__FILE__,__LINE__,A);
#define DO_CHECK_WITH_2_ARGUMENTS(K,F,A,B) Illuminate::DO_##F##_##K(__FILE__,__LINE__,A,B);
#define DO_CHECK_WITH_3_ARGUMENTS(K,F,A,B,C) Illuminate::DO_##F##_##K(__FILE__,__LINE__,A,B,C);
//@+node:gcross.20101206161648.1615: *3* DO_TEST_X
#define DO_TEST_OF_KIND(FILE,LINE,expression,message,doRegisterFailure) { if(not (expression)) { Illuminate::Test::doRegisterFailure(FILE,LINE,message); } }
#define DO_TEST_ASSERT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,registerFatalFailure)
#define DO_TEST_EXPECT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,registerFailure)
//@+node:gcross.20101206161648.1520: ** Checks
//@+node:gcross.20101206161648.1618: *3* EQ
#define EQ_EXPRESSION(expected_value,actual_value) (expected_value) == (actual_value)
#define EQ_MESSAGE(expected_value,actual_value) (boost::format("Actual value <%1%> does not match the expected value <%2%>") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(EQ,2)
#define ASSERT_EQ(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,EQ,A,B)
#define EXPECT_EQ(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,EQ,A,B)
//@+node:gcross.20101206161648.1814: *3* NEAR
#define NEAR_EXPRESSION(expected_value,actual_value,absolute_error) abs((expected_value) - (actual_value)) <=  absolute_error
#define NEAR_MESSAGE(expected_value,actual_value,absolute_error) (boost::format("Actual value <%1%> does not match the expected value <%2%> within an absolute tolerance of <%3%>") % (actual_value) % (expected_value) % (absolute_error)).str()
DEFINE_CHECKS(NEAR,3)
#define ASSERT_NEAR(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(ASSERT,NEAR,A,B,C)
#define EXPECT_NEAR(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(EXPECT,NEAR,A,B,C)
//@+node:gcross.20101206161648.1622: *3* TRUE
#define TRUE_EXPRESSION(expression,_) expression
#define TRUE_MESSAGE(_,expression) (boost::format("Assertion failed: %1%") % expression).str()
DEFINE_CHECKS(TRUE,2)
#define ASSERT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,TRUE,A,#A)
#define EXPECT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,TRUE,A,#A)
//@+node:gcross.20101206161648.1598: ** Failures
//@+node:gcross.20101206161648.1599: *3* FAIL
#define FAIL(message) Illuminate::Test::registerFailure(__FILE__,__LINE__,(message))
//@+node:gcross.20101206161648.1601: *3* FATALLY_FAIL
#define FATALLY_FAIL(message) Illuminate::Test::registerFatalFailure(__FILE__,__LINE__,(message))
//@-others

#endif
//@-leo
