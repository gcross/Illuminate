#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @thin CMakeLists.txt
add_library(illuminate
    node.cpp
    suite.cpp
    test.cpp
    visitors/plain_printer.cpp
)

install (TARGETS illuminate DESTINATION lib)
#@-leo
