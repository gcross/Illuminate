#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @thin CMakeLists.txt
add_library(illuminate
    node.cpp
    suite.cpp
    root.cpp
    test.cpp
    test_printers.cpp
    test_worker.cpp
    test_worker_group.cpp
    utils.cpp
    visitors/indented_output.cpp
    visitors/test_future.cpp
    visitors/test_queue.cpp
)

add_library(illuminate-main
    main.cpp
)

install (
    TARGETS
        illuminate
        illuminate-main
    DESTINATION lib
)
#@-leo
