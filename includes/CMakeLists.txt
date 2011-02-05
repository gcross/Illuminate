#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1312: * @thin CMakeLists.txt
install (
    FILES
        illuminate.hpp
    DESTINATION include
)

install (
    FILES
        illuminate/color_codes.hpp
        illuminate/core.hpp
        illuminate/macros.hpp
        illuminate/runners.hpp
        illuminate/test_worker.hpp
        illuminate/test_worker_group.hpp
    DESTINATION include/illuminate
)

install (
    FILES
        illuminate/visitors/indented_output.hpp
        illuminate/visitors/printer.hpp
        illuminate/visitors/queuer.hpp
    DESTINATION include/illuminate/visitors
)


install (
    FILES
        illuminate/visitors/result/future.hpp
        illuminate/visitors/result/printer.hpp
        illuminate/visitors/result/runner.hpp
    DESTINATION include/illuminate/visitors/result
)
#@-leo
