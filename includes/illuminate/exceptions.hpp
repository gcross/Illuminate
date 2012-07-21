#ifndef ILLUMINATE_EXCEPTIONS_HPP
#define ILLUMINATE_EXCEPTIONS_HPP

// Includes {{{
#include <exception>
#include <string>
// }}}

namespace Illuminate {

struct TestIdTooLargeException : std::exception {
    unsigned int test_id, maximum_test_id;
    std::string message;
    TestIdTooLargeException(unsigned int test_id, unsigned int maximum_test_id);
    virtual char const* what() const throw();
    virtual ~TestIdTooLargeException() throw();
};

}

#endif
