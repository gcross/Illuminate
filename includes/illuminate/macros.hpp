/*! \file macros.hpp
    \brief Macros for defining test suite/cases and performing checks.
*/

#ifndef ILLUMINATE_MACROS_HPP
#define ILLUMINATE_MACROS_HPP

// Includes {{{
#include <boost/format.hpp>
// }}}

// Define the test source file macro if not already defined {{{
#ifndef TEST_SOURCE_FILE
    #define TEST_SOURCE_FILE TEST_SOURCE_FILE
#endif
// }}}

// Test declarations {{{
/*! \brief These macros define tests and test suites.
    \defgroup DECLARATIONS Declarations
    \details Note that in the name displayed to the user all the underscores will be replaced with spaces and then leading and trailing whitespace will be trimmed.
*/

// Test cases {{{
#define DEFINE_TEST_CASE(caseName,skipped) \
    static void TEST_CASE_RUNNER_##caseName(); \
    static Illuminate::Test TEST_CASE_##caseName(Illuminate::underscoresToSpaces(#caseName),getParentSuite(),TEST_CASE_RUNNER_##caseName,skipped); \
    static void TEST_CASE_RUNNER_##caseName()

/*! \brief Defines a test case named \a caseName.
    \ingroup DECLARATIONS
*/
/*! The contents of the test should be supplied within curly brackets ({}'s) immediately following the macro as in the following example:

\include_example{reference-TEST_CASE}
*/
#define TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::none)

/*! \brief Defines a test case named \a caseName, but indicates that the test should be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_CASE, but the test body is ignored and the test is tagged as being skipped.

\include_example{reference-DONT_TEST_CASE}
*/
#define DONT_TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::make_optional(true))

/*! \brief Defines a test case named \a caseName, and runs it even if its parent is flagged to be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_CASE, but it overrides the skip flag of its parent to make sure the test body is run.

\include_example{reference-MUST_TEST_CASE}
*/
#define MUST_TEST_CASE(caseName) DEFINE_TEST_CASE(caseName,boost::make_optional(false))
// }}}
// Test suites {{{
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

\include_example{reference-TEST_SUITE}
*/
#define TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::none)

/*! \brief Defines a test suite named \a suiteName, but indicates that the suite should be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_SUITE, but all of the children will be skipped (unless individually re-enabled using MUST_TEST_SUITE(suiteName) or MUST_TEST_CASE(caseName).

\include_example{reference-DONT_TEST_SUITE}
*/
#define DONT_TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::make_optional(true))

/*! \brief Defines a test suite named \a suiteName, and runs it even if its parent is flagged to be skipped.
    \ingroup DECLARATIONS
*/
/*! This macro is like #TEST_SUITE, but it overrides the skip flag of its parent to make sure the test suite is run.

\include_example{reference-MUST_TEST_SUITE}
*/
#define MUST_TEST_SUITE(suiteName) DEFINE_TEST_SUITE(suiteName,boost::make_optional(false))
// }}}

// }}}

// Helpers {{{
// DEFINE_CHECK_WITH_X_ARGUMENTS {{{
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
// }}}
// DEFINE_CHECKS {{{
#define DEFINE_CHECKS(F,N) \
    DEFINE_CHECK_WITH_##N##_ARGUMENTS(ASSERT,F) \
    DEFINE_CHECK_WITH_##N##_ARGUMENTS(EXPECT,F)
// }}}
// DO_CHECK_WITH_X_ARGUMENTS {{{
#define DO_CHECK_WITH_1_ARGUMENTS(K,F,A) Illuminate::DO_##F##_##K(TEST_SOURCE_FILE,__LINE__,A);
#define DO_CHECK_WITH_2_ARGUMENTS(K,F,A,B) Illuminate::DO_##F##_##K(TEST_SOURCE_FILE,__LINE__,A,B);
#define DO_CHECK_WITH_3_ARGUMENTS(K,F,A,B,C) Illuminate::DO_##F##_##K(TEST_SOURCE_FILE,__LINE__,A,B,C);
#define DO_CHECK_WITH_4_ARGUMENTS(K,F,A,B,C,D) Illuminate::DO_##F##_##K(TEST_SOURCE_FILE,__LINE__,A,B,C,D);
#define DO_CHECK_WITH_5_ARGUMENTS(K,F,A,B,C,D,E) Illuminate::DO_##F##_##K(TEST_SOURCE_FILE,__LINE__,A,B,C,D,E);
// }}}
// DO_TEST_X {{{
#define DO_TEST_OF_KIND(FILE,LINE,expression,message,fatal) { if(not (expression)) { Illuminate::Test::registerFailure(FILE,LINE,message,fatal); } }
#define DO_TEST_ASSERT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,true)
#define DO_TEST_EXPECT(FILE,LINE,expression,message) DO_TEST_OF_KIND(FILE,LINE,expression,message,false)
// }}}
// }}}

// Checks {{{
/*! \defgroup CHECKS Checks

    These macros perform various checks within test cases.  For every kind of check there is an ASSERT and an EXPECT variant;  the difference is that the former treats failure as being fatal and immediately terminates the test, whereas the latter merely logs the failure and allows the test to proceed.
*/

// Relation {{{
/*! \defgroup RELATION_CHECKS Relation checks
    \brief These macros check that two expressions are equal in value.
    \ingroup CHECKS
*/

// Equality {{{
/*! \defgroup EQ_CHECKS EQ [=] (equality)
    \brief These macros check that two expressions are equal in value.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same, as long as comparing them for equality is supported, as is illustrated in the following example:

\include_example{reference-EQ-strings}

*/
#define EQ_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) == (value_2)
#define EQ_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> does not match %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(EQ,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A and \a B are equal}
    \ingroup EQ_CHECKS

\include_example{reference-ASSERT_EQ}
*/
#define ASSERT_EQ(A,B) ASSERT_EQ_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A and \a B are equal}
    \ingroup EQ_CHECKS

\include_example{reference-EXPECT_EQ}
*/
#define EXPECT_EQ(A,B) EXPECT_EQ_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{EQ}
    \ingroup EQ_CHECKS

\include_example{reference-ASSERT_EQ_VAL}
*/
#define ASSERT_EQ_VAL(A,B) ASSERT_EQ_LABELED(#A,A,"the expected value",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{EQ}
    \ingroup EQ_CHECKS

\include_example{reference-EXPECT_EQ_VAL}
*/
#define EXPECT_EQ_VAL(A,B) EXPECT_EQ_LABELED(#A,A,"the expected value",B)

/*! \brief \ASSERT_REL_LABELED_MESSAGE{\a B and \a D are equal}
    \ingroup EQ_CHECKS

\include_example{reference-ASSERT_EQ_LABELED}
*/
#define ASSERT_EQ_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,EQ,A,B,C,D)

/*! \brief \EXPECT_REL_LABELED_MESSAGE{\a B and \a D are equal}
    \ingroup EQ_CHECKS

\include_example{reference-EXPECT_EQ_LABELED}
*/
#define EXPECT_EQ_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,EQ,A,B,C,D)
// }}}
// Inequality {{{
/*! \defgroup NE_CHECKS NE [≠] (inequality)
    \brief These macros check that two expressions are not equal in value.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same, as long as comparing them for inequality is supported, as is illustrated in the following example:

\include_example{reference-NE-strings}
*/
#define NE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) != (value_2)
#define NE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> matches %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(NE,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A and \a B are \b not equal}
    \ingroup NE_CHECKS

\include_example{reference-ASSERT_NE}
*/
#define ASSERT_NE(A,B) ASSERT_NE_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A and \a B are \b not equal}
    \ingroup NE_CHECKS

\include_example{reference-EXPECT_NE}
*/
#define EXPECT_NE(A,B) EXPECT_NE_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{NE}
    \ingroup NE_CHECKS

\include_example{reference-ASSERT_NE_VAL}
*/
#define ASSERT_NE_VAL(A,B) ASSERT_NE_LABELED(#A,A,"the unexpected value",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{NE}
    \ingroup NE_CHECKS

\include_example{reference-EXPECT_NE_VAL}
*/
#define EXPECT_NE_VAL(A,B) EXPECT_NE_LABELED(#A,A,"the unexpected value",B)

/*! \brief \ASSERT_REL_LABELED_MESSAGE{\a B and \a D are \b not equal}
    \ingroup NE_CHECKS

\include_example{reference-ASSERT_NE_LABELED}
*/
#define ASSERT_NE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,NE,A,B,C,D)

/*! \brief \EXPECT_REL_LABELED_MESSAGE{\a B and \a D are \b not equal}
    \ingroup NE_CHECKS

\include_example{reference-EXPECT_NE_LABELED}
*/
#define EXPECT_NE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,NE,A,B,C,D)
// }}}
// Greater or equal {{{
/*! \defgroup GE_CHECKS GE [≥] (greater than or equal to)
    \brief These macros check that the first expression is greater than or equal to the second.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same as long as comparing them using the >= operator is supported.
*/
#define GE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) >= (value_2)
#define GE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is less than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GE,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A ≥ \a B}
    \ingroup GE_CHECKS

\include_example{reference-ASSERT_GE}
*/
#define ASSERT_GE(A,B) ASSERT_GE_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A ≥ \a B}
    \ingroup GE_CHECKS

\include_example{reference-EXPECT_GE}
*/
#define EXPECT_GE(A,B) EXPECT_GE_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{GE}
    \ingroup GE_CHECKS

\include_example{reference-ASSERT_GE_VAL}
*/
#define ASSERT_GE_VAL(A,B) ASSERT_GE_LABELED(#A,A,"the expected lower bound",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{GE}
    \ingroup GE_CHECKS

\include_example{reference-EXPECT_GE_VAL}
*/
#define EXPECT_GE_VAL(A,B) EXPECT_GE_LABELED(#A,A,"the expected lower bound",B)

/*! \brief Checks that \a B ≥ \a D, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup GE_CHECKS

\include_example{reference-ASSERT_GE_LABELED}
*/
#define ASSERT_GE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GE,A,B,C,D)

/*! \brief Checks that \a B ≥ \a D, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup GE_CHECKS

\include_example{reference-EXPECT_GE_LABELED}
*/
#define EXPECT_GE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GE,A,B,C,D)
// }}}
// Greater than {{{
/*! \defgroup GT_CHECKS GT [>] (greater than)
    \brief These macros check that the first expression is greater than the second.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same as long as comparing them using the > operator is supported.
*/
#define GT_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) > (value_2)
#define GT_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is less than or equal to %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(GT,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A > \a B}
    \ingroup GT_CHECKS

\include_example{reference-ASSERT_GT}
*/
#define ASSERT_GT(A,B) ASSERT_GT_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A > \a B}
    \ingroup GT_CHECKS

\include_example{reference-EXPECT_GT}
*/
#define EXPECT_GT(A,B) EXPECT_GT_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{GT}
    \ingroup GT_CHECKS

\include_example{reference-ASSERT_GT_VAL}
*/
#define ASSERT_GT_VAL(A,B) ASSERT_GT_LABELED(#A,A,"the expected strict lower bound",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{GT}
    \ingroup GT_CHECKS

\include_example{reference-EXPECT_GT_VAL}
*/
#define EXPECT_GT_VAL(A,B) EXPECT_GT_LABELED(#A,A,"the expected strict lower bound",B)

/*! \brief Checks that \a B > \a D, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup GT_CHECKS

\include_example{reference-ASSERT_GT_LABELED}
*/
#define ASSERT_GT_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,GT,A,B,C,D)

/*! \brief Checks that \a B > \a D, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup GT_CHECKS

\include_example{reference-EXPECT_GT_LABELED}
*/
#define EXPECT_GT_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,GT,A,B,C,D)
// }}}
// Less or equal {{{
/*! \defgroup LE_CHECKS LE [≤] (less than or equal to)
    \brief These macros check that the first expression is less than or equal to the second.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same as long as comparing them using the <= operator is supported.
*/
#define LE_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) <= (value_2)
#define LE_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LE,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A ≤ \a B}
    \ingroup LE_CHECKS

\include_example{reference-ASSERT_LE}
*/
#define ASSERT_LE(A,B) ASSERT_LE_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A ≤ \a B}
    \ingroup LE_CHECKS

\include_example{reference-EXPECT_LE}
*/
#define EXPECT_LE(A,B) EXPECT_LE_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{LE}
    \ingroup LE_CHECKS

\include_example{reference-ASSERT_LE_VAL}
*/
#define ASSERT_LE_VAL(A,B) ASSERT_LE_LABELED(#A,A,"the expected upper bound",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{LE}
    \ingroup LE_CHECKS

\include_example{reference-EXPECT_LE_VAL}
*/
#define EXPECT_LE_VAL(A,B) EXPECT_LE_LABELED(#A,A,"the expected upper bound",B)

/*! \brief Checks that \a B ≤ \a D, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup LE_CHECKS

\include_example{reference-ASSERT_LE_LABELED}
*/
#define ASSERT_LE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LE,A,B,C,D)

/*! \brief Checks that \a B ≤ \a D, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup LE_CHECKS

\include_example{reference-EXPECT_LE_LABELED}
*/
#define EXPECT_LE_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LE,A,B,C,D)
// }}}
// Less than {{{
/*! \defgroup LT_CHECKS LT [<] (less than)
    \brief These macros check that the first expression is less than the second.
    \ingroup RELATION_CHECKS

\note The types of the two operands need not be the same as long as comparing them using the < operator is supported.
*/
#define LT_EXPRESSION(name_1,value_1,name_2,value_2) (value_1) < (value_2)
#define LT_MESSAGE(name_1,value_1,name_2,value_2) (boost::format("%1% <%2%> is greater than or equal to %3% <%4%>") % (name_1) % (value_1) % (name_2) % (value_2)).str()
DEFINE_CHECKS(LT,4)

/*! \brief \ASSERT_REL_MESSAGE{\a A < \a B}
    \ingroup LT_CHECKS

\include_example{reference-ASSERT_LT}
*/
#define ASSERT_LT(A,B) ASSERT_LT_LABELED(#A,A,#B,B)

/*! \brief \EXPECT_REL_MESSAGE{\a A < \a B}
    \ingroup LT_CHECKS

\include_example{reference-EXPECT_LT}
*/
#define EXPECT_LT(A,B) EXPECT_LT_LABELED(#A,A,#B,B)

/*! \brief \ASSERT_REL_VAL_MESSAGE{LT}
    \ingroup LT_CHECKS

\include_example{reference-ASSERT_LT_VAL}
*/
#define ASSERT_LT_VAL(A,B) ASSERT_LT_LABELED(#A,A,"the expected strict upper bound",B)

/*! \brief \EXPECT_REL_VAL_MESSAGE{LT}
    \ingroup LT_CHECKS

\include_example{reference-EXPECT_LT_VAL}
*/
#define EXPECT_LT_VAL(A,B) EXPECT_LT_LABELED(#A,A,"the expected strict upper bound",B)

/*! \brief Checks that \a B < \a D, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup LT_CHECKS

\include_example{reference-ASSERT_LT_LABELED}
*/
#define ASSERT_LT_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(ASSERT,LT,A,B,C,D)

/*! \brief Checks that \a B < \a D, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup LT_CHECKS

\include_example{reference-EXPECT_LT_LABELED}
*/
#define EXPECT_LT_LABELED(A,B,C,D) DO_CHECK_WITH_4_ARGUMENTS(EXPECT,LT,A,B,C,D)
// }}}
// Near (absolutely) {{{
/*! \defgroup NEAR_ABS_CHECKS NEAR_ABS [≈] (absolutely approximately equal)
    \brief These macros check that two expressions are equal in value within an absolute tolerance.
    \ingroup RELATION_CHECKS

Specifically, x_NEAR_ABS_y(a,b,c) checks that \f$|a-b| \le c\f$.
*/
#define NEAR_ABS_EXPRESSION(name_1,value_1,name_2,value_2,absolute_error) (std::abs((value_1)-(value_2)) <= (absolute_error))
#define NEAR_ABS_MESSAGE(name_1,value_1,name_2,value_2,absolute_error) (boost::format("%|| <%|.15|> does not match %|| <%|.15|> within an absolute tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (absolute_error)).str()
DEFINE_CHECKS(NEAR_ABS,5)

/*! \brief \ASSERT_REL_MESSAGE{\a A and \a B are approximately equal within an absolute tolerance of \a C}
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-ASSERT_NEAR_ABS}
*/
#define ASSERT_NEAR_ABS(A,B,C) ASSERT_NEAR_ABS_LABELED(#A,A,#B,B,C)

/*! \brief \EXPECT_REL_MESSAGE{\a A and \a B are approximately equal within an absolute tolerance of \a C}
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-EXPECT_NEAR_ABS}
*/
#define EXPECT_NEAR_ABS(A,B,C) EXPECT_NEAR_ABS_LABELED(#A,A,#B,B,C)

/*! \brief \ASSERT_REL_VAL_MESSAGE{NEAR_ABS}
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-ASSERT_NEAR_ABS_VAL}
*/
#define ASSERT_NEAR_ABS_VAL(A,B,C) ASSERT_NEAR_ABS_LABELED(#A,A,"the expected value",B,C)

/*! \brief \EXPECT_REL_VAL_MESSAGE{NEAR_ABS}
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-EXPECT_NEAR_ABS_VAL}
*/
#define EXPECT_NEAR_ABS_VAL(A,B,C) EXPECT_NEAR_ABS_LABELED(#A,A,"the expected value",B,C)

/*! \brief Checks that \a B and \a D are approximately equal within an absolute tolerance of \a E, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-ASSERT_NEAR_ABS_LABELED}
*/
#define ASSERT_NEAR_ABS_LABELED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_ABS,A,B,C,D,E)

/*! \brief Checks that \a B and \a D are approximately equal within an absolute tolerance of \a E, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup NEAR_ABS_CHECKS

\include_example{reference-EXPECT_NEAR_ABS_LABELED}
*/
#define EXPECT_NEAR_ABS_LABELED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_ABS,A,B,C,D,E)
// }}}
// Near (relatively) {{{
/*! \defgroup NEAR_REL_CHECKS NEAR_REL [≈] (relatively approximately equal)
    \brief These macros check that two expressions are equal in value within a relative tolerance.
    \ingroup RELATION_CHECKS

Specifically, x_NEAR_REL_y(a,b,c) checks that either \f$|a|+|b| \le c\f$ (that is, both a and b are approximately 0) or that \f$\frac{|a-b|}{(|a|+|b|)/2} \le c\f$
*/
#define NEAR_REL_EXPRESSION(name_1,value_1,name_2,value_2,relative_error) (((std::abs(value_1)+std::abs(value_2))/2 <= (relative_error)) || (std::abs((value_1)-(value_2))/((std::abs(value_1)+std::abs(value_2))/2) <= (relative_error)))
#define NEAR_REL_MESSAGE(name_1,value_1,name_2,value_2,relative_error) (boost::format("%|| <%|.15|> does not match %|| <%|.15|> within a relative tolerance of %||") % (name_1) % (value_1) % (name_2) % (value_2) % (relative_error)).str()
DEFINE_CHECKS(NEAR_REL,5)

/*! \brief \ASSERT_REL_MESSAGE{\a A and \a B are approximately equal within a relative tolerance of \a C}
    \ingroup NEAR_REL_CHECKS

\include_example{reference-ASSERT_NEAR_REL}
*/
#define ASSERT_NEAR_REL(A,B,C) ASSERT_NEAR_REL_LABELED(#A,A,#B,B,C)

/*! \brief \EXPECT_REL_MESSAGE{\a A and \a B are approximately equal within a relative tolerance of \a C}
    \ingroup NEAR_REL_CHECKS

\include_example{reference-EXPECT_NEAR_REL}
*/
#define EXPECT_NEAR_REL(A,B,C) EXPECT_NEAR_REL_LABELED(#A,A,#B,B,C)

/*! \brief \ASSERT_REL_VAL_MESSAGE{NEAR_REL}
    \ingroup NEAR_REL_CHECKS

\include_example{reference-ASSERT_NEAR_REL_VAL}
*/
#define ASSERT_NEAR_REL_VAL(A,B,C) ASSERT_NEAR_REL_LABELED(#A,A,"the expected value",B,C)

/*! \brief \EXPECT_REL_VAL_MESSAGE{NEAR_REL}
    \ingroup NEAR_REL_CHECKS

\include_example{reference-EXPECT_NEAR_REL_VAL}
*/
#define EXPECT_NEAR_REL_VAL(A,B,C) EXPECT_NEAR_REL_LABELED(#A,A,"the expected value",B,C)

/*! \brief Checks that \a B and \a D are approximately equal within a relative tolerance of \a E, and if not registers a failure labeling these values with the respective names \a A and \a C, and then terminates the test.
    \ingroup NEAR_REL_CHECKS

\include_example{reference-ASSERT_NEAR_REL_LABELED}
*/
#define ASSERT_NEAR_REL_LABELED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(ASSERT,NEAR_REL,A,B,C,D,E)

/*! \brief Checks that \a B and \a D are approximately equal within a relative tolerance of \a E, and if not registers a failure labeling these values with the respective names \a A and \a C.
    \ingroup NEAR_REL_CHECKS

\include_example{reference-EXPECT_NEAR_REL_LABELED}
*/
#define EXPECT_NEAR_REL_LABELED(A,B,C,D,E) DO_CHECK_WITH_5_ARGUMENTS(EXPECT,NEAR_REL,A,B,C,D,E)
// }}}

// }}}
// Boolean {{{
/*! \defgroup BOOLEAN_CHECKS Boolean checks
    \brief These macros check for the truth or falsity of an expression.
    \ingroup CHECKS
*/

// True {{{
/*! \defgroup TRUE_CHECKS TRUE
    \brief These macros check that the given boolean expression is true.
    \ingroup BOOLEAN_CHECKS
*/
#define TRUE_EXPRESSION(expression,_) (expression)
#define TRUE_MESSAGE(_,expression) (boost::format("%1% is not true") % expression).str()
DEFINE_CHECKS(TRUE,2)

/*! \brief Checks that \a A is true, and if not registers a failure and terminates the test.
    \ingroup TRUE_CHECKS

\include_example{reference-ASSERT_TRUE}
*/
#define ASSERT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,TRUE,A,#A)

/*! \brief Checks that \a A is true, and if not registers a failure.
    \ingroup TRUE_CHECKS

\include_example{reference-EXPECT_TRUE}
*/
#define EXPECT_TRUE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,TRUE,A,#A)
// }}}
// False {{{
/*! \defgroup FALSE_CHECKS FALSE
    \brief These macros check that the given boolean expression is false.
    \ingroup BOOLEAN_CHECKS
*/
#define FALSE_EXPRESSION(expression,_) (!(expression))
#define FALSE_MESSAGE(_,expression) (boost::format("%1% is not false") % expression).str()
DEFINE_CHECKS(FALSE,2)

/*! \brief Checks that \a A is false, and if not registers a failure and terminates the test.
    \ingroup FALSE_CHECKS

\include_example{reference-ASSERT_FALSE}
*/
#define ASSERT_FALSE(A) DO_CHECK_WITH_2_ARGUMENTS(ASSERT,FALSE,A,#A)

/*! \brief Checks that \a A is false, and if not registers a failure.
    \ingroup FALSE_CHECKS

\include_example{reference-EXPECT_FALSE}
*/
#define EXPECT_FALSE(A) DO_CHECK_WITH_2_ARGUMENTS(EXPECT,FALSE,A,#A)
// }}}

// }}}

// }}}

// Expected failures {{{
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
                    Illuminate::Test::registerFailure(TEST_SOURCE_FILE,_ILLUMINATE_KNOWN_FAIL_line_number,"Expected failure(s) did not occur.",_ILLUMINATE_KNOWN_FAIL_fatal); \
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
                Illuminate::Test::registerFailure(TEST_SOURCE_FILE,_ILLUMINATE_THROWS_line_number,"Exception " #exception_type " was not thrown.",_ILLUMINATE_THROWS_fatal); \
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
// }}}

// Failures {{{
/*! \defgroup FORCED_FAILURES Forced failures
    \brief These macros force a failure message to be displayed.
    \ingroup CHECKS
*/

/*! \brief Raises a failure with the given message.
    \ingroup FORCED_FAILURES

\include_example{reference-FAIL}
*/
#define FAIL(message) Illuminate::Test::registerFailure(TEST_SOURCE_FILE,__LINE__,(message),false);

/*! \brief Raises a failure with the given message, and then terminates the test.
    \ingroup FORCED_FAILURES

\include_example{reference-FATALLY_FAIL}
*/
#define FATALLY_FAIL(message) Illuminate::Test::registerFailure(TEST_SOURCE_FILE,__LINE__,(message),true);
// }}}

#endif
