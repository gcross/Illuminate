// Includes {{{
#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>

#include "illuminate/test_tree.hpp"
// }}}

// Usings {{{
using boost::trim;

using std::string;
// }}}

namespace Illuminate {

string underscoresToSpaces(string const& old_string) { // {{{
    string new_string = old_string;
    BOOST_FOREACH(char& c, new_string) {
        if(c == '_') { c = ' '; }
    }
    trim(new_string);
    return new_string;
} // }}}

}
