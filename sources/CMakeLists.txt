#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1278: * @file CMakeLists.txt
add_library(illuminate SHARED
    color_codes
    exceptions
    node
    suite
    root
    runners
    slave
    test
    test_worker
    test_worker_group
    utils
    test_result_fetchers/future
    visitors/indented_output
    visitors/result.cpp
    visitors/result/printer
)
target_link_libraries(illuminate ${Boost_LIBRARIES})

add_library(illuminate-main SHARED
    main.cpp
)
target_link_libraries(illuminate-main illuminate)

install (
    TARGETS
        illuminate
        illuminate-main
    DESTINATION ${LIBRARY_INSTALLATION_DIRECTORY}
    EXPORT Illuminate-targets
)
#@-leo
