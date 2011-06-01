#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @file CMakeLists.txt
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
target_link_libraries(illuminate ${Boost_LIBRARIES})

add_library(illuminate-main
    main.cpp
)
target_link_libraries(illuminate-main illuminate)

install (
    TARGETS
        illuminate
        illuminate-main
    DESTINATION lib/Illuminate-${version}
    EXPORT Illuminate-targets
)
#@-leo
