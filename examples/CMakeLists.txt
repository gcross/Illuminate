#@+leo-ver=5-thin
#@+node:gcross.20110626224331.2628: * @file CMakeLists.txt
#@@language python

#@+others
#@+node:gcross.20110715235201.1473: ** addExample
function(addExample example-output example-sources additional-libraries additional-options)
    add_definitions(-D__FILE__="example.cpp")
    get_filename_component(example-name ${example-output} NAME_WE)
    add_executable(${example-name} EXCLUDE_FROM_ALL ${example-sources})
    target_link_libraries(${example-name} illuminate ${additional-libraries})
    set_property(
        TARGET ${example-name}
        PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/examples
    )
    set(example-output-generated ${CMAKE_BINARY_DIR}/tests/examples/${example-output})
    add_custom_target(${example-output}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tests/examples
        COMMAND ${example-name} -o ${example-output-generated} ${additional-options}
        DEPENDS ${example-name}
    )
    add_test(
        NAME ${example-name}
        COMMAND
            ${CMAKE_COMMAND}
                -E compare_files
                    ${CMAKE_CURRENT_SOURCE_DIR}/${example-output}
                    ${example-output-generated}
    )
    set(tests-dependencies ${tests-dependencies} ${example-output} PARENT_SCOPE)
endfunction(addExample)
#@+node:gcross.20110715235201.1486: ** addSimpleExample
macro(addSimpleExample example-name)
    addExample(${example-name}.out ${example-name}.cpp illuminate-main "")
endmacro(addSimpleExample)
#@-others

#@+<< Tests >>
#@+node:gcross.20110715235201.1474: ** << Tests >>
#@+others
#@+node:gcross.20110715235201.1487: *3* Simple examples
foreach(simple-example-name
    chapter1-simple-test
    chapter1-simple-test-broken
    chapter1-test-with-multiple-expects
    chapter1-test-with-multiple-asserts
    chapter1-test-with-multiple-expects-and-asserts
    chapter1-suffix-variants
)
    addSimpleExample(${simple-example-name})
endforeach(simple-example-name)
#@-others
#@-<< Tests >>

message(STATUS "Test dependencies = " ${tests-dependencies})

add_custom_target(tests DEPENDS ${tests-dependencies})
#@-leo
