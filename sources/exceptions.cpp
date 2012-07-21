// Includes {{{
#include <boost/format.hpp>

#include "illuminate/exceptions.hpp"
// }}}

// Usings {{{
using boost::format;

using std::exception;
using std::string;
// }}}

namespace Illuminate {

TestIdTooLargeException::TestIdTooLargeException(unsigned int test_id, unsigned int maximum_test_id)
  : test_id(test_id)
  , maximum_test_id(maximum_test_id)
  , message((format("No such test id %1% (%1% > %2%).") % test_id % maximum_test_id).str())
{}

char const* TestIdTooLargeException::what() const throw() {
    return message.c_str();
}
TestIdTooLargeException::~TestIdTooLargeException() throw() {}

}
