//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1548: * @file indented_output.hpp
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

/*! \file indented_output.hpp
    \brief Illuminate::IndentedOutputVisitor class
*/

#ifndef ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP
#define ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1549: ** << Includes >>
#include <boost/format.hpp>
#include <iostream>

#include "../visitor.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+others
//@+node:gcross.20101206161648.1551: ** class IndentedOutputVisitor
//! A visitor which indents the output corresponding to the nest level of the current suite.
class IndentedOutputVisitor : public virtual Visitor {
protected:
    //! the current indentation level
    int indentation;
    //! the current output stream
    std::ostream& out;

    //! Constructor
    /*! \param out the current output stream */
    IndentedOutputVisitor(std::ostream& out);

    //! write \c s with the current level of indentation
    void writeIndented(boost::format const& s);
    //! write \c s with the current level of indentation
    void writeIndented(std::string const& s);
    //! write \c s with the current level of indentation and a trailing newline character
    void writeIndentedLine(boost::format const& s);
    //! write \c s with the current level of indentation and a trailing newline character
    void writeIndentedLine(std::string const& s);

    virtual void enter(Suite const& suite);
    virtual void exit(Suite const& suite);

    //! Called for each suite (upon entrance).
    virtual void suite(Suite const& suite) = 0;
};
//@-others

}

#endif
//@-leo
