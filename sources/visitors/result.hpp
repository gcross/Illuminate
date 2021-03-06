//@+leo-ver=5-thin
//@+node:gcross.20110601150226.2617: * @file result.hpp
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

/*! \file result.hpp
    \brief Illuminate::ResultVisitor class
*/

#ifndef ILLUMINATE_VISITORS_RESULT_HPP
#define ILLUMINATE_VISITORS_RESULT_HPP

//@+<< Includes >>
//@+node:gcross.20110601121230.1623: ** << Includes >>
#include "../visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20110203224841.1945: ** class ResultVisitor
//! Test result visitor.
/*!
This class extends the Visitor interface with additional methods that are called with information about the result of running a test.

Note that normally the user will not implement the Visitor::test method directly but instead will delegate to another class which will run a test and then call the methods defined in this class based on the result of running the test.
*/
class ResultVisitor : public virtual Visitor {
protected:
    //! Called when a test has been skipped.
    virtual void testSkipped(Test const& test) = 0;
    //! Called when a test has been started.
    virtual void testStarted(Test const& test) = 0;
    //! Called when a test has been passed.
    virtual void testPassed(Test const& test) = 0;
    //! Called when a test has been failed.
    /*!
    \param test the test that failed
    \param failures a list of descriptions of the failures that were recorded for the test
    */
    virtual void testFailed(Test const& test,std::vector<std::string> const& failures) = 0;
};
//@-others

}

#endif
//@-leo
