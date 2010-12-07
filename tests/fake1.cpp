//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1791: * @thin fake1.cpp
//@@language cplusplus
//@@tabwidth -4
//@+<< Licence >>
//@+node:gcross.20101206161648.1792: ** << Licence >>
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
//@+node:gcross.20101206161648.1793: ** << Includes >>
#include "illuminate.hpp"
//@-<< Includes >>

namespace {
    unsigned i = 0;
    unsigned x()
    {
        return 1;
    }
} // namespace

static unsigned y()
{
    return 1;
}

TEST_SUITE(StaticLink1) {

TEST_CASE(IncStatic1)
{
    ++i;
    // varibles in anonymous namespace cannot be seen by other files
    ASSERT_EQ(1u, i);
    ASSERT_TRUE(1 == x() && "functions in anonymous namespace cannot be redefined from other files");
    ASSERT_TRUE(1 == y() && "static function has no external linkage");
}

} // suite
//@-leo
