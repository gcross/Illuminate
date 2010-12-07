#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1312: * @thin CMakeLists.txt
install (
    FILES
        illuminate.hpp
    DESTINATION include
)

install (
    FILES
        illuminate/core.hpp
        illuminate/macros.hpp
    DESTINATION include/illuminate
)

install (
    FILES
        illuminate/visitors/ansi_test_runner.hpp
        illuminate/visitors/indented_output.hpp
        illuminate/visitors/plain_printer.hpp
        illuminate/visitors/plain_test_runner.hpp
    DESTINATION include/illuminate/visitors
)
#@-leo
