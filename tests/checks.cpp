//@+leo-ver=5-thin
//@+node:gcross.20110222154148.1568: * @thin checks.cpp
//@@language cplusplus
//@@tabwidth -4
//@+<< Licence >>
//@+node:gcross.20110222154148.1569: ** << Licence >>
//@+at
// unit--, a simple and easy-to-use unit test aid for C++
// Copyright (C) 2005~2006  Tsong Chong
// birdiez@126.com
// 
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
// 
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
// 
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//@@c
//@-<< Licence >>
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
//@+node:gcross.20110222154148.1597: *4* NEAR
TEST_CASE(NEAR) {
    EXPECT_NEAR(1,1,0)
    EXPECT_NEAR(1,1.09,0.1)
    BEGIN_EXPECT_FAIL { EXPECT_NEAR(1,1.11,0.1); } END_EXPECT_FAIL

    ASSERT_NEAR(1,1,0)
    ASSERT_NEAR(1,1.09,0.1)
    BEGIN_EXPECT_FAIL { ASSERT_NEAR(1,1.11,0.1); } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1599: *4* NEAR_RELATIVE
TEST_CASE(NEAR_RELATIVE) {
    EXPECT_NEAR_RELATIVE(10,10,0)
    EXPECT_NEAR_RELATIVE(10,10.9,0.1)
    BEGIN_EXPECT_FAIL { EXPECT_NEAR_RELATIVE(10,11.1,0.1); } END_EXPECT_FAIL

    ASSERT_NEAR_RELATIVE(10,10,0)
    ASSERT_NEAR_RELATIVE(10,10.9,0.1)
    BEGIN_EXPECT_FAIL { ASSERT_NEAR_RELATIVE(10,11.1,0.1); } END_EXPECT_FAIL
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
