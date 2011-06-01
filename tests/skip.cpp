//@+leo-ver=5-thin
//@+node:gcross.20110222194651.1610: * @file skip.cpp
//@@language cplusplus
//@@tabwidth -4
//@+<< License >>
//@+node:gcross.20110222194651.1611: ** << License >>
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
//@+node:gcross.20110222194651.1612: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

//@+others
//@+node:gcross.20110222194651.1613: ** Tests
TEST_SUITE(Skip) {

//@+others
//@+node:gcross.20110222194651.1626: *3* skipped test
SKIP_TEST_CASE(skipped_test) {
    FATALLY_FAIL("This test should have been skipped.");
}
//@+node:gcross.20110222194651.1628: *3* unskipped test
UNSKIP_TEST_CASE(unskipped_test) {}
//@+node:gcross.20110222194651.1629: *3* skipped suite
SKIP_TEST_SUITE(skipped_suite) {

//@+others
//@+node:gcross.20110222194651.1631: *4* skipped test
TEST_CASE(skipped_test) {
    FATALLY_FAIL("This test should have been skipped.");
}
//@+node:gcross.20110222194651.1633: *4* unskipped test
UNSKIP_TEST_CASE(unskipped_test) {}
//@+node:gcross.20110222194651.1637: *4* unskipped suite
UNSKIP_TEST_SUITE(unskipped_suite) {

//@+others
//@+node:gcross.20110222194651.1638: *5* skipped test
SKIP_TEST_CASE(skipped_test) {
    FATALLY_FAIL("This test should have been skipped.");
}
//@+node:gcross.20110222194651.1639: *5* unskipped test
TEST_CASE(unskipped_test) {}
//@-others

}
//@-others

}
//@-others

}
//@-others
//@-leo
