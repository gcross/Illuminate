//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1800: * @file template.cpp
//@@language cplusplus
//@@tabwidth -4
//@+<< Licence >>
//@+node:gcross.20101206161648.1792: ** << Licence >>
//@+at
// Copyright (c) 2011, Gregory Crosswhite <gcrosswhite@gmail.com>
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
// 
// ==================================================================================
// 
// unit--, a simple and easy-to-use unit test aid for C++
// Copyright (C) 2005~2006  Tsong Chong <birdiez@126.com>
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
//@+node:gcross.20101206161648.1802: ** << Includes >>
#include <algorithm>
#include <numeric>
#include <vector>

#include "illuminate.hpp"

using std::vector;
//@-<< Includes >>

TEST_SUITE(TemplateSuite) {

template <typename T>
void testAlgorithms()
{

    vector<T> ve(100, 1);
    partial_sum(ve.begin(), ve.end(), ve.begin());

    ASSERT_TRUE(ve.size() > 0);
    ASSERT_TRUE(1 == ve[0]);
    for (unsigned i = 1; i < ve.size(); ++i) {
        ASSERT_EQ(ve[i - 1] + 1, ve[i]);
    }
}

TEST_CASE(IntCase)
{
    testAlgorithms<int>();
}

TEST_CASE(UnsignedCase)
{
    testAlgorithms<unsigned>();
}

} // suite
//@-leo
