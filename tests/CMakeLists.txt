#@+leo-ver=5-thin
#@+node:gcross.20101206161648.1788: * @thin CMakeLists.txt
add_executable(test EXCLUDE_FROM_ALL
    examples
    fake1
    fake2
    template
)
target_link_libraries(test illuminate-main illuminate ${Boost_LIBRARIES})
set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@-leo
