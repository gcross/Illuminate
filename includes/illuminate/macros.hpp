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
#define DEFINE_CHECK_WITH_4_ARGUMENTS(K,F) \
    namespace Illuminate {\
        template<class T1,class T2,class T3,class T4> void DO_##F##_##K(const char* filename, int line_number, const T1& a, const T2& b, const T3& c, const T4& d) {\
            DO_TEST_##K(filename,line_number,F##_EXPRESSION(a,b,c,d),F##_MESSAGE(a,b,c,d));\
        }\
    }
#include <iostream>
#define DEFINE_CHECK_WITH_5_ARGUMENTS(K,F) \
    namespace Illuminate {\
        template<class T1,class T2,class T3,class T4,class T5> void DO_##F##_##K(const char* filename, int line_number, const T1& a, const T2& b, const T3& c, const T4& d, const T5& e) {\
            DO_TEST_##K(filename,line_number,F##_EXPRESSION(a,b,c,d,e),F##_MESSAGE(a,b,c,d,e));\
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
#define DO_CHECK_WITH_4_ARGUMENTS(K,F,A,B,C,D) Illuminate::DO_##F##_##K(__FILE__,__LINE__,A,B,C,D);
#define DO_CHECK_WITH_5_ARGUMENTS(K,F,A,B,C,D,E) Illuminate::DO_##F##_##K(__FILE__,__LINE__,A,B,C,D,E);
//@+node:gcross.20101206161648.1615: *3* DO_TEST_X
#define DO_TEST_OF_KIND(FILE,LINE,expression,message,fatal) { if(not (expression)) { Illuminate::Test::registerFailure(FILE,LINE,message,fatal); } }
#define DO_TEST_ASSERT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,true)
#define DO_TEST_EXPECT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,false)
//@+node:gcross.20101206161648.1520: ** Checks
//@+node:gcross.20101206161648.1618: *3* EQ
#define EQ_EXPRESSION(expected_value,actual_value) (expected_value) == (actual_value)
#define EQ_MESSAGE(expected_value,actual_value) (boost::format("Actual value <%1%> does not match the expected value <%2%>") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(EQ,2)
#define ASSERT_EQ(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,EQ,A,B)
#define EXPECT_EQ(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,EQ,A,B)

#define EQ_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) EQ_EXPRESSION(value_1,value_2)
#define EQ_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> does not match %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(EQ_NAMED,4)
#define ASSERT_EQ_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,EQ_NAMED,A,B,C,D)
#define EXPECT_EQ_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,EQ_NAMED,A,B,C,D)

#define ASSERT_EQ_QUOTED(A,B) ASSERT_EQ_NAMED(#A,A,#B,B)
#define EXPECT_EQ_QUOTED(A,B) EXPECT_EQ_NAMED(#A,A,#B,B)
//@+node:gcross.20110130203213.1497: *3* GE
#define GE_EXPRESSION(expected_value,actual_value) (expected_value) >= (actual_value)
#define GE_MESSAGE(expected_value,actual_value) (boost::format("%1% < %2%") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(GE,2)
#define ASSERT_GE(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,GE,A,B)
#define EXPECT_GE(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,GE,A,B)

#define GE_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) GE_EXPRESSION(value_1,value_2)
#define GE_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is less than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GE_NAMED,4)
#define ASSERT_GE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GE_NAMED,A,B,C,D)
#define EXPECT_GE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GE_NAMED,A,B,C,D)

#define ASSERT_GE_QUOTED(A,B) ASSERT_GE_NAMED(#A,A,#B,B)
#define EXPECT_GE_QUOTED(A,B) EXPECT_GE_NAMED(#A,A,#B,B)
//@+node:gcross.20110130203213.1501: *3* GT
#define GT_EXPRESSION(expected_value,actual_value) (expected_value) > (actual_value)
#define GT_MESSAGE(expected_value,actual_value) (boost::format("%1% <= %2%") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(GT,2)
#define ASSERT_GT(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,GT,A,B)
#define EXPECT_GT(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,GT,A,B)

#define GT_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) GT_EXPRESSION(value_1,value_2)
#define GT_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is not greater than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GT_NAMED,4)
#define ASSERT_GT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GT_NAMED,A,B,C,D)
#define EXPECT_GT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GT_NAMED,A,B,C,D)

#define ASSERT_GT_QUOTED(A,B) ASSERT_GT_NAMED(#A,A,#B,B)
#define EXPECT_GT_QUOTED(A,B) EXPECT_GT_NAMED(#A,A,#B,B)
//@+node:gcross.20110130203213.1499: *3* LE
#define LE_EXPRESSION(expected_value,actual_value) (expected_value) <= (actual_value)
#define LE_MESSAGE(expected_value,actual_value) (boost::format("%1% > %2%") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(LE,2)
#define ASSERT_LE(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,LE,A,B)
#define EXPECT_LE(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,LE,A,B)

#define LE_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) LE_EXPRESSION(value_1,value_2)
#define LE_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LE_NAMED,4)
#define ASSERT_LE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LE_NAMED,A,B,C,D)
#define EXPECT_LE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LE_NAMED,A,B,C,D)

#define ASSERT_LE_QUOTED(A,B) ASSERT_LE_NAMED(#A,A,#B,B)
#define EXPECT_LE_QUOTED(A,B) EXPECT_LE_NAMED(#A,A,#B,B)
//@+node:gcross.20110130203213.1503: *3* LT
#define LT_EXPRESSION(expected_value,actual_value) (expected_value) < (actual_value)
#define LT_MESSAGE(expected_value,actual_value) (boost::format("%1% >= %2%") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(LT,2)
#define ASSERT_LT(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,LT,A,B)
#define EXPECT_LT(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,LT,A,B)

#define LT_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) LT_EXPRESSION(value_1,value_2)
#define LT_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is not less than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LT_NAMED,4)
#define ASSERT_LT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LT_NAMED,A,B,C,D)
#define EXPECT_LT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LT_NAMED,A,B,C,D)

#define ASSERT_LT_QUOTED(A,B) ASSERT_LT_NAMED(#A,A,#B,B)
#define EXPECT_LT_QUOTED(A,B) EXPECT_LT_NAMED(#A,A,#B,B)
//@+node:gcross.20110130204958.1501: *3* NE
#define NE_EXPRESSION(expected_value,actual_value) (expected_value) != (actual_value)
#define NE_MESSAGE(expected_value,actual_value) (boost::format("%1% > %2%") % (actual_value) % (expected_value)).str()
DEFINE_CHECKS(NE,2)
#define ASSERT_NE(A,B) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,NE,A,B)
#define EXPECT_NE(A,B) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,NE,A,B)

#define NE_NAMED_EXPRESSION(name_1,value_1,name_2,value_2) NE_EXPRESSION(value_1,value_2)
#define NE_NAMED_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(NE_NAMED,4)
#define ASSERT_NE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,NE_NAMED,A,B,C,D)
#define EXPECT_NE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,NE_NAMED,A,B,C,D)

#define ASSERT_NE_QUOTED(A,B) ASSERT_NE_NAMED(#A,A,#B,B)
#define EXPECT_NE_QUOTED(A,B) EXPECT_NE_NAMED(#A,A,#B,B)
//@+node:gcross.20101206161648.1814: *3* NEAR
#define NEAR_EXPRESSION(expected_value,actual_value,absolute_error) abs((expected_value) - (actual_value)) <= absolute_error
#define NEAR_MESSAGE(expected_value,actual_value,absolute_error) (boost::format("Actual value %|.15| does not match the expected value %|.15| within an absolute tolerance of %||") % (actual_value) % (expected_value) % (absolute_error)).str()
DEFINE_CHECKS(NEAR,3)
#define ASSERT_NEAR(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(ASSERT,NEAR,A,B,C)
#define EXPECT_NEAR(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(EXPECT,NEAR,A,B,C)

#define NEAR_NAMED_EXPRESSION(name_1,value_1,name_2,value_2,absolute_error) abs((value_2) - (value_1)) <= absolute_error
#define NEAR_NAMED_MESSAGE(name_1,value_1,name_2,value_2,absolute_error) (boost::format("%|| %|.15| does not match %|| %|.15| within an absolute tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (absolute_error)).str()
DEFINE_CHECKS(NEAR_NAMED,5)
#define ASSERT_NEAR_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_NAMED,A,B,C,D,E)
#define EXPECT_NEAR_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_NAMED,A,B,C,D,E)

#define ASSERT_NEAR_QUOTED(A,B,C) ASSERT_NEAR_NAMED(#A,A,#B,B,C)
#define EXPECT_NEAR_QUOTED(A,B,C) EXPECT_NEAR_NAMED(#A,A,#B,B,C)
//@+node:gcross.20110219100916.1564: *3* NEAR_RELATIVE
#define NEAR_RELATIVE_EXPRESSION(expected_value,actual_value,relative_error) ((abs(expected_value)+abs(actual_value))/2 <= relative_error) || (abs((expected_value) - (actual_value))/(abs(expected_value)+abs(actual_value)+relative_error) <= relative_error)
#define NEAR_RELATIVE_MESSAGE(expected_value,actual_value,relative_error) (boost::format("Actual value %|.15| does not match the expected value %|.15| within a relative tolerance of %||") % (actual_value) % (expected_value) % (relative_error)).str()
DEFINE_CHECKS(NEAR_RELATIVE,3)
#define ASSERT_NEAR_RELATIVE(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(ASSERT,NEAR_RELATIVE,A,B,C)
#define EXPECT_NEAR_RELATIVE(A,B,C) DO_CHECK_WITH_3_ARGUMENTS(EXPECT,NEAR_RELATIVE,A,B,C)

#define NEAR_RELATIVE_NAMED_EXPRESSION(name_1,value_1,name_2,value_2,relative_error) NEAR_RELATIVE_EXPRESSION(value_1,value_2,relative_error)
#define NEAR_RELATIVE_NAMED_MESSAGE(name_1,value_1,name_2,value_2,relative_error) (boost::format("%|| %|.15| does not match %|| %|.15| within a relative tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (relative_error)).str()
DEFINE_CHECKS(NEAR_RELATIVE_NAMED,5)
#define ASSERT_NEAR_RELATIVE_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_RELATIVE_NAMED,A,B,C,D,E)
#define EXPECT_NEAR_RELATIVE_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_RELATIVE_NAMED,A,B,C,D,E)

#define ASSERT_NEAR_RELATIVE_QUOTED(A,B,C) ASSERT_NEAR_RELATIVE_NAMED(#A,A,#B,B,C)
#define EXPECT_NEAR_RELATIVE_QUOTED(A,B,C) EXPECT_NEAR_RELATIVE_NAMED(#A,A,#B,B,C)
//@+node:gcross.20101206161648.1622: *3* TRUE
#define TRUE_EXPRESSION(expression,_) expression
#define TRUE_MESSAGE(_,expression) (boost::format("Assertion failed: %1%") % expression).str()
DEFINE_CHECKS(TRUE,2)
#define ASSERT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,TRUE,A,#A)
#define EXPECT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,TRUE,A,#A)
//@+node:gcross.20110204201608.2058: *3* FALSE
#define FALSE_EXPRESSION(expression,_) (!expression)
#define FALSE_MESSAGE(_,expression) (boost::format("Anti-assertion failed: %1%") % expression).str()
DEFINE_CHECKS(FALSE,2)
#define ASSERT_FALSE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,FALSE,A,#A)
#define EXPECT_FALSE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,FALSE,A,#A)
//@+node:gcross.20110222132831.1572: ** Expected failures
#define _ILLUMINATE_BEGIN_KNOWN_FAIL \
        { \
            bool _ILLUMINATE_KNOWN_FAIL_exception_thrown = false; \
            unsigned int const \
                  _ILLUMINATE_KNOWN_FAIL_line_number = __LINE__ \
                , _ILLUMINATE_KNOWN_FAIL_old_number_of_failures = Illuminate::Test::countFailures(); \
            try {

#define _ILLUMINATE_END_KNOWN_FAIL \
            } catch(...) { _ILLUMINATE_KNOWN_FAIL_exception_thrown = true; } \
                unsigned int const \
                    _ILLUMINATE_KNOWN_FAIL_new_number_of_failures = Illuminate::Test::countFailures(); \
                Illuminate::Test::eraseFailuresAfter(_ILLUMINATE_KNOWN_FAIL_old_number_of_failures); \
                if(!_ILLUMINATE_KNOWN_FAIL_exception_thrown && _ILLUMINATE_KNOWN_FAIL_new_number_of_failures <= _ILLUMINATE_KNOWN_FAIL_old_number_of_failures) { \
                    Illuminate::Test::registerFailure(__FILE__,_ILLUMINATE_KNOWN_FAIL_line_number,"Expected failure(s) did not occur.",_ILLUMINATE_KNOWN_FAIL_fatal); \
                } \
        }

#define BEGIN_ASSERT_FAIL \
    { \
        bool const _ILLUMINATE_KNOWN_FAIL_fatal = true; \
        _ILLUMINATE_BEGIN_KNOWN_FAIL

#define END_ASSERT_FAIL \
        _ILLUMINATE_END_KNOWN_FAIL \
    }

#define BEGIN_EXPECT_FAIL \
    { \
        bool const _ILLUMINATE_KNOWN_FAIL_fatal = false; \
        _ILLUMINATE_BEGIN_KNOWN_FAIL

#define END_EXPECT_FAIL \
        _ILLUMINATE_END_KNOWN_FAIL \
    }

#define _ILLUMINATE_BEGIN_THROWS \
        { \
            bool _ILLUMINATE_THROWS_exception_thrown = false; \
            unsigned int const _ILLUMINATE_THROWS_line_number = __LINE__; \
            try {

#define _ILLUMINATE_END_THROWS(exception_type) \
            } catch(exception_type const& e) { _ILLUMINATE_THROWS_exception_thrown = true; } \
            if(!_ILLUMINATE_THROWS_exception_thrown) { \
                Illuminate::Test::registerFailure(__FILE__,_ILLUMINATE_THROWS_line_number,"Exception " #exception_type " was not thrown.",_ILLUMINATE_THROWS_fatal); \
            } \
        }

#define BEGIN_ASSERT_THROWS \
    { \
        bool _ILLUMINATE_THROWS_fatal = true; \
        _ILLUMINATE_BEGIN_THROWS

#define END_ASSERT_THROWS(exception_type) \
        _ILLUMINATE_END_THROWS(exception_type) \
    }

#define BEGIN_EXPECT_THROWS \
    { \
        bool _ILLUMINATE_THROWS_fatal = false; \
        _ILLUMINATE_BEGIN_THROWS

#define END_EXPECT_THROWS(exception_type) \
        _ILLUMINATE_END_THROWS(exception_type) \
    }
//@+node:gcross.20101206161648.1598: ** Failures
//@+node:gcross.20101206161648.1599: *3* FAIL
#define FAIL(message) Illuminate::Test::registerFailure(__FILE__,__LINE__,(message),false)
//@+node:gcross.20101206161648.1601: *3* FATALLY_FAIL
#define FATALLY_FAIL(message) Illuminate::Test::registerFailure(__FILE__,__LINE__,(message),true)
//@-others

#endif
//@-leo
