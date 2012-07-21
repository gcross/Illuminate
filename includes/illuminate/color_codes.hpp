/*! \file color_codes.hpp
    \brief Classes and functions for defining color code escape sequences to produce prettier test result output.
*/

#ifndef ILLUMINATE_COLOR_CODES_HPP
#define ILLUMINATE_COLOR_CODES_HPP

#include <boost/any.hpp>
#include <boost/format.hpp>
#include <iosfwd>
#include <string>
#include <vector>

namespace Illuminate {

class Suite;
class Test;

//! Structure specifing color code escape sequences
struct ColorCodes { // {{{
    //! Constructor
    ColorCodes(const std::string& suite, const std::string& test, const std::string& skip, const std::string& pass, const std::string& fail, const std::string& reset);

    std::string
        //! color code escape sequence for suites
        suite,
        //! color code escape sequence for tests
        test,
        //! color code escape sequence for skipped messsage
        skip,
        //! color code escape sequence for passed message
        pass,
        //! color code escape sequence for failed messages
        fail,
        //! escape sequence to reset the terminal to the default color mode
        reset;
    
    //! Built-in color codes for plain text --- that is, no color codes at all.
    static const ColorCodes plain;

    //! Color codes using ANSI escape sequences
    /*!
    Suites are white, test cases are yellow, passes are green, failures are red, skips are purple.
    */
    static const ColorCodes ANSI;

    //! Constructs PASSED :-) using the appropriate color codes.
    boost::format passed() const;

    //! Constructs FAILED :-( using the appropriate color codes.
    boost::format failed() const;

    //! Constructs the given failure message using appropriate color codes.
    boost::format failure(std::string const& m) const;

    //! Constructs the number of tests message using appropriate color codes.
    boost::format numberOfFailedTests(unsigned int number_of_failed_tests) const;

    //! Constructs the suite entered string using appropriate color codes.
    boost::format suiteEntered(Suite const& suite) const;

    //! Constructs the test path string using appropriate color codes.
    boost::format testPath(Test const& test) const;

    //! Constructs the test name string using appropriate color codes.
    boost::format testName(Test const& test) const;

    //! Constructs the test name (with (skipped) if appropriate) string using appropriate color codes.
    boost::format testNameAndSkipped(Test const& test) const;

    //! Constructs the test skipped string using appropriate color codes.
    boost::format testSkipped() const;

    //! Constructs the test started string using appropriate color codes.
    boost::format testStarted() const;
}; // }}}

//! Built-in supported color codes.
enum Coloring { // {{{
//! Color codes using ANSI escape sequences
/*!
Suites are white, test cases are yellow, passes are green, failures are red, skips are purple.
*/
ANSI_COLORING,
//! Non-existent color codes
PLAIN_COLORING
}; // }}}

//! Validates user input value for color codes.
/*!
\note This function is primarily intended to be used by boost::program_options.
*/
void validate(
      boost::any& v
    , std::vector<std::string> const& values
    , Coloring* target_type
    , int
);

}

#endif
