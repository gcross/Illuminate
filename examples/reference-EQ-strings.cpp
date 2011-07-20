#include "illuminate.hpp"
#include <string>

TEST_CASE(EQ_using_strings) {
    std::string hello_world = "Hello, world!";
    EXPECT_EQ_VAL(hello_world,"Hello, world!")
    EXPECT_EQ_VAL(hello_world,"Hello, planet!")
}
