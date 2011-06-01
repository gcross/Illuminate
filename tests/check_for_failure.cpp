//@+leo-ver=5-thin
//@+node:gcross.20110222132831.1576: * @file check_for_failure.cpp
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
