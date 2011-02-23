//@+leo-ver=5-thin
//@+node:gcross.20101206142257.1399: * @thin macros.hpp
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

/*! \file macros.hpp
    \brief Macros for defining test suite/cases and performing checks.
*/

#ifndef ILLUMINATE_MACROS_HPP
#define ILLUMINATE_MACROS_HPP

//@+<< Includes >>
//@+node:gcross.20101209013121.1492: ** << Includes >>
#include <boost/format.hpp>
//@-<< Includes >>

//@+others
//@+node:gcross.20101206142257.1405: ** Test declarations
/*! \brief These macros define tests and test suites.
    \defgroup DECLARATIONS Test declarations
    \details Note that in the name displayed to the user all the underscores will be replaced with spaces and then leading and trailing whitespace will be trimmed.
*/
//@+node:gcross.20101206142257.1407: *3* TEST_CASE
#define DEFINE_TEST_CASE(caseName,skipped) \
    static void TEST_CASE_RUNNER_##caseName(); \
    static Illuminate::Test TEST_CASE_##caseName(Illuminate::underscoresToSpaces(#caseName),getParentSuite(),TEST_CASE_RUNNER_##caseName,skipped); \
    static void TEST_CASE_RUNNER_##caseName()

/*! \brief Defines a test case named \a caseName.
    \ingroup DECLARATIONS
*/
/*! The contents of the test should be supplied within curly brackets ({}'s) immediately following the macro as in the following example:

    \code
    TEST_CASE(MyTest) {
        ...
        ASSERT_TRUE(expression);
    }
    \endcode
*/
#define TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::none)

/*! \brief Defines a test case named \a caseName, but indicates that the test should be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_CASE, but the test body is ignored and the test is tagged as being skipped.
*/
#define SKIP_TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::make_optional(true))

/*! \brief Defines a test case named \a caseName, and runs it even if its parent is flagged to be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_CASE, but it overrides the skip flag of its parent to make sure the test body is run.
*/
#define UNSKIP_TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::make_optional(false))
//@+node:gcross.20101206142257.1406: *3* TEST_SUITE
#define DEFINE_TEST_SUITE(suiteName,skipped) \
    namespace SUITE_##suiteName { \
        static Illuminate::Suite& _getParentSuite() { \
            static Illuminate::Suite& suite = getParentSuite().lookupSuite(Illuminate::underscoresToSpaces(#suiteName),skipped); \
            return suite; \
        } \
        static Illuminate::Suite& getParentSuite() { return _getParentSuite(); } \
    } \
    namespace SUITE_##suiteName

/*! \brief Defines a test suite named \a suiteName.
    \ingroup DECLARATIONS
*/
/*! Suites may contain a mixture of test cases and nested test suites in any order.  The contents of the suite should be supplied within curly brackets ({}'s) immediately following the macro as in the following example:

    \code
    TEST_SUITE(Suite) {
        TEST_SUITE(NestedSuite1) { ... }
        TEST_SUITE(NestedSuite2) { ... }
        ...
        TEST_CASE(Test1) { ... }
        TEST_CASE(Test2) { ... }
        ...
    }
    \endcode
*/
#define TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::none)

/*! \brief Defines a test suite named \a suiteName, but indicates that the suite should be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_SUITE, but all of the children will be skipped (unless individually UNSKIPped).
*/
#define SKIP_TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::make_optional(true))

/*! \brief Defines a test suite named \a suiteName, and runs it even if its parent is flagged to be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_SUITE, but it overrides the skip flag of its parent to make sure the test suite is run.
*/
#define UNSKIP_TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::make_optional(false))
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
/*! \defgroup CHECKS Checks

    These macros perform various checks within test cases.  For every kind of check there is an ASSERT and an EXPECT variant;  the difference is that the former treats failure as being fatal and immediately terminates the test, whereas the latter merely logs the failure and allows the test to proceed.
*/
//@+node:gcross.20110221195111.1565: *3* Relation
/*! \defgroup RELATION_CHECKS Relation checks
    \brief These macros check that two expressions are equal in value.
    \ingroup CHECKS
*/
//@+node:gcross.20101206161648.1618: *4* EQ
/*! \defgroup EQ_CHECKS EQ [=] (equality)
    \brief These macros check that two expressions are equal in value.
    \ingroup RELATION_CHECKS
*/
#define EQ_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) == (value_2)
#define EQ_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> does not match %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(EQ,4)

/*! \brief Checks that \a A and \a B are equal; registers a fatal failure otherwise.
    \ingroup EQ_CHECKS
*/
#define ASSERT_EQ(A,B) ASSERT_EQ_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A and \a B are equal; registers a non-fatal failure otherwise.
    \ingroup EQ_CHECKS
*/
#define EXPECT_EQ(A,B) EXPECT_EQ_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_EQ, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup EQ_CHECKS
*/
#define ASSERT_EQ_VAL(A,B) ASSERT_EQ_NAMED(#A,A,"the expected value",B)

/*! \brief Like #EXPECT_EQ, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup EQ_CHECKS
*/
#define EXPECT_EQ_VAL(A,B) EXPECT_EQ_NAMED(#A,A,"the expected value",B)

/*! \brief Checks that \a B and \a D are equal; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup EQ_CHECKS
*/
#define ASSERT_EQ_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,EQ,A,B,C,D)

/*! \brief Checks that \a B and \a D are equal; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup EQ_CHECKS
*/
#define EXPECT_EQ_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,EQ,A,B,C,D)
//@+node:gcross.20110222121027.1867: *4* NE
/*! \defgroup NE_CHECKS NE [≠] (inequality)
    \brief These macros check that two expressions are not equal in value.
    \ingroup RELATION_CHECKS
*/
#define NE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) != (value_2)
#define NE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> matches %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(NE,4)

/*! \brief Checks that \a A and \a B are not equal; registers a fatal failure otherwise.
    \ingroup NE_CHECKS
*/
#define ASSERT_NE(A,B) ASSERT_NE_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A and \a B are not equal; registers a non-fatal failure otherwise.
    \ingroup NE_CHECKS
*/
#define EXPECT_NE(A,B) EXPECT_NE_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_NE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NE_CHECKS
*/
#define ASSERT_NE_VAL(A,B) ASSERT_NE_NAMED(#A,A,"the unexpected value",B)

/*! \brief Like #EXPECT_NE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NE_CHECKS
*/
#define EXPECT_NE_VAL(A,B) EXPECT_NE_NAMED(#A,A,"the unexpected value",B)

/*! \brief Checks that \a B and \a D are not equal; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NE_CHECKS
*/
#define ASSERT_NE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,NE,A,B,C,D)

/*! \brief Checks that \a B and \a D are not equal; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NE_CHECKS
*/
#define EXPECT_NE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,NE,A,B,C,D)
//@+node:gcross.20110130203213.1497: *4* GE
/*! \defgroup GE_CHECKS GE [≥] (greater than or equal to)
    \brief These macros check that the first expression is greater than or equal to the second.
    \ingroup RELATION_CHECKS
*/
#define GE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) >= (value_2)
#define GE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is less than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GE,4)

/*! \brief Checks that \a A ≥ \a B; registers a fatal failure otherwise.
    \ingroup GE_CHECKS
*/
#define ASSERT_GE(A,B) ASSERT_GE_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A ≥ \a B; registers a non-fatal failure otherwise.
    \ingroup GE_CHECKS
*/
#define EXPECT_GE(A,B) EXPECT_GE_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_GE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup GE_CHECKS
*/
#define ASSERT_GE_VAL(A,B) ASSERT_GE_NAMED(#A,A,"the expected lower bound",B)

/*! \brief Like #EXPECT_GE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup GE_CHECKS
*/
#define EXPECT_GE_VAL(A,B) EXPECT_GE_NAMED(#A,A,"the expected lower bound",B)

/*! \brief Checks that \a B ≥ \a D; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup GE_CHECKS
*/
#define ASSERT_GE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GE,A,B,C,D)

/*! \brief Checks that \a B ≥ \a D; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup GE_CHECKS
*/
#define EXPECT_GE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GE,A,B,C,D)
//@+node:gcross.20110222121027.1859: *4* GT
/*! \defgroup GT_CHECKS GT [>] (greater than)
    \brief These macros check that the first expression is greater than the second.
    \ingroup RELATION_CHECKS
*/
#define GT_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) > (value_2)
#define GT_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is less than or equal to %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GT,4)

/*! \brief Checks that \a A > \a B; registers a fatal failure otherwise.
    \ingroup GT_CHECKS
*/
#define ASSERT_GT(A,B) ASSERT_GT_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A > \a B; registers a non-fatal failure otherwise.
    \ingroup GT_CHECKS
*/
#define EXPECT_GT(A,B) EXPECT_GT_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_GT, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup GT_CHECKS
*/
#define ASSERT_GT_VAL(A,B) ASSERT_GT_NAMED(#A,A,"the expected strict lower bound",B)

/*! \brief Like #EXPECT_GT, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup GT_CHECKS
*/
#define EXPECT_GT_VAL(A,B) EXPECT_GT_NAMED(#A,A,"the expected strict lower bound",B)

/*! \brief Checks that \a B > \a D; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup GT_CHECKS
*/
#define ASSERT_GT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GT,A,B,C,D)

/*! \brief Checks that \a B > \a D; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup GT_CHECKS
*/
#define EXPECT_GT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GT,A,B,C,D)
//@+node:gcross.20110222121027.1861: *4* LE
/*! \defgroup LE_CHECKS LE [≤] (less than or equal to)
    \brief These macros check that the first expression is less than or equal to the second.
    \ingroup RELATION_CHECKS
*/
#define LE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) <= (value_2)
#define LE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LE,4)

/*! \brief Checks that \a A ≤ \a B; registers a fatal failure otherwise.
    \ingroup LE_CHECKS
*/
#define ASSERT_LE(A,B) ASSERT_LE_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A ≤ \a B; registers a non-fatal failure otherwise.
    \ingroup LE_CHECKS
*/
#define EXPECT_LE(A,B) EXPECT_LE_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_LE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup LE_CHECKS
*/
#define ASSERT_LE_VAL(A,B) ASSERT_LE_NAMED(#A,A,"the expected upper bound",B)

/*! \brief Like #EXPECT_LE, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup LE_CHECKS
*/
#define EXPECT_LE_VAL(A,B) EXPECT_LE_NAMED(#A,A,"the expected upper bound",B)

/*! \brief Checks that \a B ≤ \a D; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup LE_CHECKS
*/
#define ASSERT_LE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LE,A,B,C,D)

/*! \brief Checks that \a B ≤ \a D; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup LE_CHECKS
*/
#define EXPECT_LE_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LE,A,B,C,D)
//@+node:gcross.20110222121027.1863: *4* LT
/*! \defgroup LT_CHECKS LT [<] (less than)
    \brief These macros check that the first expression is less than the second.
    \ingroup RELATION_CHECKS
*/
#define LT_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) < (value_2)
#define LT_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than or equal to %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LT,4)

/*! \brief Checks that \a A < \a B; registers a fatal failure otherwise.
    \ingroup LT_CHECKS
*/
#define ASSERT_LT(A,B) ASSERT_LT_NAMED(#A,A,#B,B)

/*! \brief Checks that \a A < \a B; registers a non-fatal failure otherwise.
    \ingroup LT_CHECKS
*/
#define EXPECT_LT(A,B) EXPECT_LT_NAMED(#A,A,#B,B)

/*! \brief Like #ASSERT_LT, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup LT_CHECKS
*/
#define ASSERT_LT_VAL(A,B) ASSERT_LT_NAMED(#A,A,"the expected strict upper bound",B)

/*! \brief Like #EXPECT_LT, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup LT_CHECKS
*/
#define EXPECT_LT_VAL(A,B) EXPECT_LT_NAMED(#A,A,"the expected strict upper bound",B)

/*! \brief Checks that \a B < \a D; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup LT_CHECKS
*/
#define ASSERT_LT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LT,A,B,C,D)

/*! \brief Checks that \a B < \a D; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup LT_CHECKS
*/
#define EXPECT_LT_NAMED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LT,A,B,C,D)
//@+node:gcross.20110222121027.1873: *4* NEAR_ABS
/*! \defgroup NEAR_ABS_CHECKS NEAR_ABS [≈] (absolutely approximately equal)
    \brief These macros check that two expressions are equal in value within an absolute tolerance.
    \ingroup RELATION_CHECKS
*/
#define NEAR_ABS_EXPRESSION(name_1,value_1,name_2,value_2,absolute_error) (std::abs((value_1)-(value_2)) <= absolute_error)
#define NEAR_ABS_MESSAGE(name_1,value_1,name_2,value_2,absolute_error) (boost::format("%|| %|.15| does not match %|| %|.15| within an absolute tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (absolute_error)).str()
DEFINE_CHECKS(NEAR_ABS,5)

/*! \brief Checks that \a A and \a B are approximately equal within an absolute tolerance of \a C; registers a fatal failure otherwise.
    \ingroup NEAR_ABS_CHECKS
*/
#define ASSERT_NEAR_ABS(A,B,C) ASSERT_NEAR_ABS_NAMED(#A,A,#B,B,C)

/*! \brief Checks that \a A and \a B are approximately equal within an absolute tolerance of \a C; registers a non-fatal failure otherwise.
    \ingroup NEAR_ABS_CHECKS
*/
#define EXPECT_NEAR_ABS(A,B,C) EXPECT_NEAR_ABS_NAMED(#A,A,#B,B,C)

/*! \brief Like #ASSERT_NEAR_ABS, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NEAR_ABS_CHECKS
*/
#define ASSERT_NEAR_ABS_VAL(A,B,C) ASSERT_NEAR_ABS_NAMED(#A,A,"the expected value",B,C)

/*! \brief Like #EXPECT_NEAR_ABS, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NEAR_ABS_CHECKS
*/
#define EXPECT_NEAR_ABS_VAL(A,B,C) EXPECT_NEAR_ABS_NAMED(#A,A,"the expected value",B,C)

/*! \brief Checks that \a B and \a D are approximately equal within an absolute tolerance of \a E; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NEAR_ABS_CHECKS
*/
#define ASSERT_NEAR_ABS_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_ABS,A,B,C,D,E)

/*! \brief Checks that \a B and \a D are approximately equal within an absolute tolerance of \a E; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NEAR_ABS_CHECKS
*/
#define EXPECT_NEAR_ABS_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_ABS,A,B,C,D,E)
//@+node:gcross.20110222121027.1875: *4* NEAR_REL
/*! \defgroup NEAR_REL_CHECKS NEAR_REL [≈] (relatively approximately equal)
    \brief These macros check that two expressions are equal in value within a relative tolerance.
    \ingroup RELATION_CHECKS
*/
#define NEAR_REL_EXPRESSION(name_1,value_1,name_2,value_2,relative_error) (((std::abs(value_1)+std::abs(value_2))/2 <= relative_error) || (std::abs((value_1)-(value_2))/((std::abs(value_1)+std::abs(value_2))/2) <= relative_error))
#define NEAR_REL_MESSAGE(name_1,value_1,name_2,value_2,relative_error) (boost::format("%|| %|.15| does not match %|| %|.15| within a relative tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (relative_error)).str()
DEFINE_CHECKS(NEAR_REL,5)

/*! \brief Checks that \a A and \a B are approximately equal within a relative tolerance of \a C; registers a fatal failure otherwise.
    \ingroup NEAR_REL_CHECKS
*/
#define ASSERT_NEAR_REL(A,B,C) ASSERT_NEAR_REL_NAMED(#A,A,#B,B,C)

/*! \brief Checks that \a A and \a B are approximately equal within a relative tolerance of \a C; registers a non-fatal failure otherwise.
    \ingroup NEAR_REL_CHECKS
*/
#define EXPECT_NEAR_REL(A,B,C) EXPECT_NEAR_REL_NAMED(#A,A,#B,B,C)

/*! \brief Like #ASSERT_NEAR_REL, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NEAR_REL_CHECKS
*/
#define ASSERT_NEAR_REL_VAL(A,B,C) ASSERT_NEAR_REL_NAMED(#A,A,"the expected value",B,C)

/*! \brief Like #EXPECT_NEAR_REL, but only quotes the first argument in the error message.  This macro is provided for the case where \a B is an integer literal so that both quoting it and displaying its value would be redundant.
    \ingroup NEAR_REL_CHECKS
*/
#define EXPECT_NEAR_REL_VAL(A,B,C) EXPECT_NEAR_REL_NAMED(#A,A,"the expected value",B,C)

/*! \brief Checks that \a B and \a D are approximately equal within a relative tolerance of \a E; registers a fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NEAR_REL_CHECKS
*/
#define ASSERT_NEAR_REL_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_REL,A,B,C,D,E)

/*! \brief Checks that \a B and \a D are approximately equal within a relative tolerance of \a E; registers a non-fatal failure labeling these values with the respective names \a A and \a C otherwise.
    \ingroup NEAR_REL_CHECKS
*/
#define EXPECT_NEAR_REL_NAMED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_REL,A,B,C,D,E)
//@+node:gcross.20110221195111.1566: *3* Boolean
/*! \defgroup BOOLEAN_CHECKS Boolean checks
    \brief These macros check for the truth or falsity of an expression.
    \ingroup CHECKS
*/
//@+node:gcross.20101206161648.1622: *4* TRUE
/*! \defgroup TRUE_CHECKS TRUE
    \brief These macros check that the given boolean expression is true.
    \ingroup BOOLEAN_CHECKS
*/
#define TRUE_EXPRESSION(expression,_) (expression)
#define TRUE_MESSAGE(_,expression) (boost::format("Assertion failed: %1%") % expression).str()
DEFINE_CHECKS(TRUE,2)

/*! \brief Checks that \a A is true; registers a fatal failure otherwise.
    \ingroup TRUE_CHECKS
*/
#define ASSERT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,TRUE,A,#A)

/*! \brief Checks that \a A is true; registers a non-fatal failure otherwise.
    \ingroup TRUE_CHECKS
*/
#define EXPECT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,TRUE,A,#A)
//@+node:gcross.20110222121027.1877: *4* FALSE
/*! \defgroup FALSE_CHECKS FALSE
    \brief These macros check that the given boolean expression is false.
    \ingroup BOOLEAN_CHECKS
*/
#define FALSE_EXPRESSION(expression,_) (!(expression))
#define FALSE_MESSAGE(_,expression) (boost::format("Assertion failed: %1%") % expression).str()
DEFINE_CHECKS(FALSE,2)

/*! \brief Checks that \a A is false; registers a fatal failure otherwise.
    \ingroup FALSE_CHECKS
*/
#define ASSERT_FALSE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,FALSE,A,#A)

/*! \brief Checks that \a A is false; registers a non-fatal failure otherwise.
    \ingroup FALSE_CHECKS
*/
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
