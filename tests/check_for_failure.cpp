//@+leo-ver=5-thin
//@+node:gcross.20110222132831.1576: * @thin check_for_failure.cpp
//@@language cplusplus
//@@tabwidth -4
//@+<< Licence >>
//@+node:gcross.20110222132831.1577: ** << Licence >>
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
//@+node:gcross.20110222132831.1578: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20110222154148.1571: ** Tests
TEST_SUITE(CheckForFailure) {

//@+others
//@+node:gcross.20110222154148.1572: *3* detects_failed_checks
TEST_CASE(detects_failed_checks)
{
    BEGIN_ASSERT_FAIL {
        ASSERT_FALSE(true);
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        ASSERT_FALSE(true);
    } END_EXPECT_FAIL

    BEGIN_ASSERT_FAIL {
        EXPECT_FALSE(true);
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        EXPECT_FALSE(true);
    } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1573: *3* detects_thrown_exception
TEST_CASE(detects_thrown_exception)
{
    BEGIN_ASSERT_FAIL {
        throw "exception";
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        throw "exception";
    } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1577: *3* exceptions
TEST_CASE(exceptions)
{
    BEGIN_ASSERT_THROWS {
        throw 0;
    } END_ASSERT_THROWS(int)

    BEGIN_EXPECT_FAIL {
        BEGIN_ASSERT_THROWS {
        } END_ASSERT_THROWS(int)
    } END_EXPECT_FAIL

    BEGIN_EXPECT_THROWS {
        throw 0;
    } END_EXPECT_THROWS(int)

    BEGIN_EXPECT_FAIL {
        BEGIN_EXPECT_THROWS {
        } END_EXPECT_THROWS(int)
    } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1576: *3* nested_four_times
TEST_CASE(nested_four_times)
{
    BEGIN_ASSERT_FAIL {
        BEGIN_ASSERT_FAIL {
            BEGIN_ASSERT_FAIL {
                BEGIN_ASSERT_FAIL {
                } END_ASSERT_FAIL
            } END_ASSERT_FAIL
        } END_ASSERT_FAIL
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        BEGIN_EXPECT_FAIL {
            BEGIN_EXPECT_FAIL {
                BEGIN_EXPECT_FAIL {
                } END_EXPECT_FAIL
            } END_EXPECT_FAIL
        } END_EXPECT_FAIL
    } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1575: *3* nested_thrice
TEST_CASE(nested_thrice)
{
    BEGIN_ASSERT_FAIL {
        BEGIN_ASSERT_FAIL {
            BEGIN_ASSERT_FAIL {
                throw "exception";
            } END_ASSERT_FAIL
        } END_ASSERT_FAIL
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        BEGIN_EXPECT_FAIL {
            BEGIN_EXPECT_FAIL {
                throw "exception";
            } END_EXPECT_FAIL
        } END_EXPECT_FAIL
    } END_EXPECT_FAIL
}
//@+node:gcross.20110222154148.1574: *3* nested_twice
TEST_CASE(nested_twice)
{
    BEGIN_ASSERT_FAIL {
        BEGIN_ASSERT_FAIL {
        } END_ASSERT_FAIL
    } END_ASSERT_FAIL

    BEGIN_ASSERT_FAIL {
        BEGIN_EXPECT_FAIL {
        } END_EXPECT_FAIL
    } END_ASSERT_FAIL

    BEGIN_EXPECT_FAIL {
        BEGIN_ASSERT_FAIL {
        } END_ASSERT_FAIL
    } END_EXPECT_FAIL

    BEGIN_EXPECT_FAIL {
        BEGIN_EXPECT_FAIL {
        } END_EXPECT_FAIL
    } END_EXPECT_FAIL
}
//@-others

}
//@-others
//@-leo
