//@+leo-ver=5-thin
//@+node:gcross.20110222154148.1568: * @file checks.cpp
//@@language cplusplus
//@@tabwidth -4
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
//@+node:gcross.20110222154148.1570: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20110222154148.1578: ** Tests
TEST_SUITE(Checks) {

//@+others
//@+node:gcross.20110222154148.1590: *3* Relation
TEST_SUITE(Relation) {

//@+others
//@+node:gcross.20110222154148.1579: *4* EQ
TEST_CASE(EQ) {
    EXPECT_EQ(1,1)
    BEGIN_EXPECT_FAIL { EXPECT_EQ(1,2); } END_EXPECT_FAIL

    ASSERT_EQ(1,1)
    BEGIN_EXPECT_FAIL { ASSERT_EQ(1,2); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1581: *4* NE
TEST_CASE(NE) {
    EXPECT_NE(1,2)
    BEGIN_EXPECT_FAIL { EXPECT_NE(1,1); } END_EXPECT_FAIL

    ASSERT_NE(1,2)
    BEGIN_EXPECT_FAIL { ASSERT_NE(1,1); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1583: *4* GE
TEST_CASE(GE) {
    EXPECT_GE(2,1)
    EXPECT_GE(2,2)
    BEGIN_EXPECT_FAIL { EXPECT_GE(1,2); } END_EXPECT_FAIL

    ASSERT_GE(2,1)
    ASSERT_GE(2,2)
    BEGIN_EXPECT_FAIL { ASSERT_GE(1,2); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1587: *4* GT
TEST_CASE(GT) {
    EXPECT_GT(2,1)
    BEGIN_EXPECT_FAIL { EXPECT_GT(2,2); } END_EXPECT_FAIL
    BEGIN_EXPECT_FAIL { EXPECT_GT(1,2); } END_EXPECT_FAIL

    ASSERT_GT(2,1)
    BEGIN_EXPECT_FAIL { ASSERT_GT(2,2); } END_EXPECT_FAIL
    BEGIN_EXPECT_FAIL { ASSERT_GT(1,2); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1585: *4* LE
TEST_CASE(LE) {
    EXPECT_LE(1,2)
    EXPECT_LE(2,2)
    BEGIN_EXPECT_FAIL { EXPECT_LE(2,1); } END_EXPECT_FAIL

    ASSERT_LE(1,2)
    ASSERT_LE(2,2)
    BEGIN_EXPECT_FAIL { ASSERT_LE(2,1); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1589: *4* LT
TEST_CASE(LT) {
    EXPECT_LT(1,2)
    BEGIN_EXPECT_FAIL { EXPECT_LT(2,2); } END_EXPECT_FAIL
    BEGIN_EXPECT_FAIL { EXPECT_LT(2,1); } END_EXPECT_FAIL

    ASSERT_LT(1,2)
    BEGIN_EXPECT_FAIL { ASSERT_LT(2,2); } END_EXPECT_FAIL
    BEGIN_EXPECT_FAIL { ASSERT_LT(2,1); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1597: *4* NEAR_ABS
TEST_CASE(NEAR_ABS) {
    EXPECT_NEAR_ABS(1,1,0)
    EXPECT_NEAR_ABS(1,1.09,0.1)
    BEGIN_EXPECT_FAIL { EXPECT_NEAR_ABS(1,1.11,0.1); } END_EXPECT_FAIL

    ASSERT_NEAR_ABS(1,1,0)
    ASSERT_NEAR_ABS(1,1.09,0.1)
    BEGIN_EXPECT_FAIL { ASSERT_NEAR_ABS(1,1.11,0.1); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1599: *4* NEAR_REL
TEST_CASE(NEAR_REL) {
    EXPECT_NEAR_REL(10,10,0)
    EXPECT_NEAR_REL(10,10.9,0.1)
    BEGIN_EXPECT_FAIL { EXPECT_NEAR_REL(10,11.1,0.1); } END_EXPECT_FAIL

    ASSERT_NEAR_REL(10,10,0)
    ASSERT_NEAR_REL(10,10.9,0.1)
    BEGIN_EXPECT_FAIL { ASSERT_NEAR_REL(10,11.1,0.1); } END_EXPECT_FAIL
}
//@-others

}
//@+node:gcross.20110222154148.1591: *3* Boolean
TEST_SUITE(Boolean) {

//@+others
//@+node:gcross.20110222154148.1593: *4* TRUE
TEST_CASE(TRUE) {
    EXPECT_TRUE(true)
    BEGIN_EXPECT_FAIL { EXPECT_TRUE(false); } END_EXPECT_FAIL

    ASSERT_TRUE(true)
    BEGIN_EXPECT_FAIL { ASSERT_TRUE(false); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1595: *4* FALSE
TEST_CASE(FALSE) {
    EXPECT_FALSE(false)
    BEGIN_EXPECT_FAIL { EXPECT_FALSE(true); } END_EXPECT_FAIL

    ASSERT_FALSE(false)
    BEGIN_EXPECT_FAIL { ASSERT_FALSE(true); } END_EXPECT_FAIL
}
//@-others

}
//@-others

}
//@-others
//@-leo