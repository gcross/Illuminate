//@+leo-ver=5-thin
//@+node:gcross.20101206104532.1377: * @thin utils.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101206104532.1378: ** << Includes >>
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206104532.1379: ** << Usings >>
using namespace boost::algorithm;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206104532.1382: ** Functions
//@+node:gcross.20101206104532.1384: *3* underscoresToSpaces
string underscoresToSpaces(const string& old_string) {
    string new_string = old_string;
    BOOST_FOREACH(char& c, new_string) {
        if(c == '_') { c = ' '; }
    }
    trim(new_string);
    return new_string;
}
//@-others

}
//@-leo
