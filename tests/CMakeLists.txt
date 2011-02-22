#@+leo-ver=5-thin
#@+node:gcross.20101206161648.1788: * @thin CMakeLists.txt
add_executable(test EXCLUDE_FROM_ALL
    check_for_failure
    examples
    fake1
    fake2
    template
)
target_link_libraries(test illuminate-main)
set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@-leo
