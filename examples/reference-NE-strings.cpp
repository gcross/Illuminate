#include "illuminate.hpp"
#include <string>

TEST_CASE(NE_using_strings) {
    std::string hello_world = "Hello, world!";
    EXPECT_NE_VAL(hello_world,"Hello, world!")
    EXPECT_NE_VAL(hello_world,"Hello, planet!")
}
