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
        illuminate/test_printers.hpp
        illuminate/test_worker.hpp
        illuminate/test_worker_group.hpp
    DESTINATION include/illuminate
)

install (
    FILES
        illuminate/visitors/indented_output.hpp
        illuminate/visitors/test_future.hpp
        illuminate/visitors/test_queue.hpp
    DESTINATION include/illuminate/visitors
)
#@-leo
