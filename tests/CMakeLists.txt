#@+leo-ver=5-thin
#@+node:gcross.20101205214942.1919: * @thin CMakeLists.txt
#@+<< Macros >>
#@+node:gcross.20101205214942.1920: ** << Macros >>
macro(makeTestProgram program-name)
    add_executable(${program-name} EXCLUDE_FROM_ALL ${${program-name}-SOURCES})
    target_link_libraries(${program-name} illuminate illuminate-main ${Boost_LIBRARIES})
    set_property(TARGET ${program-name} PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
endmacro(makeTestProgram)
#@-<< Macros >>

#@+<< Includes >>
#@+node:gcross.20101205214942.1921: ** << Includes >>
include_directories(".")
#@-<< Includes >>

#@+others
#@+node:gcross.20101205214942.1922: ** test
set(test-SOURCES
    test.cpp
    test2.cpp
)

makeTestProgram(test)
#@-others
#@-leo
