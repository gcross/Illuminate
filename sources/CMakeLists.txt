#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @thin CMakeLists.txt
add_library(illuminate
    node.cpp
    suite.cpp
    root.cpp
    test.cpp
    utils.cpp
    visitors/indented_output.cpp
    visitors/plain_printer.cpp
    visitors/plain_test_runner.cpp
)

install (TARGETS illuminate DESTINATION lib)
#@-leo
