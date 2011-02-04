#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @thin CMakeLists.txt
add_library(illuminate
    color_codes
    node
    suite
    root
    runners
    test
    test_worker
    test_worker_group
    utils
    visitors/result/future
    visitors/result/printer
    visitors/result/runner
    visitors/indented_output
    visitors/printer
    visitors/queuer
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
