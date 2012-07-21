/*! \file indented_output.hpp
    \brief Illuminate::IndentedOutputVisitor class
*/

#ifndef ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP
#define ILLUMINATE_VISITORS_INDENTED_OUTPUT_HPP

// Includes {{{
#include <boost/format.hpp>
#include <iostream>

#include "../visitor.hpp"
// }}}

namespace Illuminate {

//! A visitor which indents the output corresponding to the nest level of the current suite.
class IndentedOutputVisitor : public virtual Visitor { // {{{
protected:
    //! the current indentation level
    int indentation;
    //! the current output stream
    std::ostream& out;

    //! Constructor
    /*! \param out the current output stream */
    IndentedOutputVisitor(std::ostream& out);

    //! write spaces to produce the current level of indentation
    void writeIndentation();
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
}; // }}}

}

#endif
