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
#@+node:gcross.20110730203014.1426: *3* Introduction
foreach(simple-example-name
    introduction-example
)
    addSimpleExample(${simple-example-name})
endforeach(simple-example-name)

#@+node:gcross.20110715235201.1487: *3* Chapter 1
foreach(simple-example-name
    chapter1-simple-test
    chapter1-simple-test-broken
    chapter1-test-with-multiple-expects
    chapter1-test-with-multiple-asserts
    chapter1-test-with-multiple-expects-and-asserts
    chapter1-suffix-variants
    chapter1-all-relations
    chapter1-approximate-equality
    chapter1-boolean-checks
    chapter1-forced-failure
)
    addSimpleExample(${simple-example-name})
endforeach(simple-example-name)

#@+node:gcross.20110725161606.1415: *3* Chapter 2
foreach(simple-example-name
    chapter2-multiple-test-cases-same-file
    chapter2-test-suites
    chapter2-nesting
    chapter2-dont-test
    chapter2-must-test
)
    addSimpleExample(${simple-example-name})
endforeach(simple-example-name)

# Not enabled by default since the exact output is compiler-dependent.
#addExample(chapter2-multiple-test-cases-multiple-files.out "chapter2-multiple-test-cases-1.cpp;chapter2-multiple-test-cases-2.cpp;chapter2-multiple-test-cases-3.cpp" illuminate-main "")
#addExample(chapter2-test-suite-multiple-files.out "chapter2-test-suite-multiple-files-1.cpp;chapter2-test-suite-multiple-files-2.cpp" illuminate-main "")
#@+node:gcross.20110725161606.1417: *3* Reference
foreach(simple-example-name
    reference-EQ-strings
    reference-ASSERT_EQ
    reference-EXPECT_EQ
    reference-ASSERT_EQ_VAL
    reference-EXPECT_EQ_VAL
    reference-ASSERT_EQ_LABELED
    reference-EXPECT_EQ_LABELED

    reference-NE-strings
    reference-ASSERT_NE
    reference-EXPECT_NE
    reference-ASSERT_NE_VAL
    reference-EXPECT_NE_VAL
    reference-ASSERT_NE_LABELED
    reference-EXPECT_NE_LABELED

    reference-ASSERT_GE
    reference-EXPECT_GE
    reference-ASSERT_GE_VAL
    reference-EXPECT_GE_VAL
    reference-ASSERT_GE_LABELED
    reference-EXPECT_GE_LABELED

    reference-ASSERT_GT
    reference-EXPECT_GT
    reference-ASSERT_GT_VAL
    reference-EXPECT_GT_VAL
    reference-ASSERT_GT_LABELED
    reference-EXPECT_GT_LABELED

    reference-ASSERT_LE
    reference-EXPECT_LE
    reference-ASSERT_LE_VAL
    reference-EXPECT_LE_VAL
    reference-ASSERT_LE_LABELED
    reference-EXPECT_LE_LABELED

    reference-ASSERT_LT
    reference-EXPECT_LT
    reference-ASSERT_LT_VAL
    reference-EXPECT_LT_VAL
    reference-ASSERT_LT_LABELED
    reference-EXPECT_LT_LABELED

    reference-ASSERT_NEAR_ABS
    reference-EXPECT_NEAR_ABS
    reference-ASSERT_NEAR_ABS_VAL
    reference-EXPECT_NEAR_ABS_VAL
    reference-ASSERT_NEAR_ABS_LABELED
    reference-EXPECT_NEAR_ABS_LABELED

    reference-ASSERT_NEAR_REL
    reference-EXPECT_NEAR_REL
    reference-ASSERT_NEAR_REL_VAL
    reference-EXPECT_NEAR_REL_VAL
    reference-ASSERT_NEAR_REL_LABELED
    reference-EXPECT_NEAR_REL_LABELED

    reference-ASSERT_TRUE
    reference-EXPECT_TRUE
    reference-ASSERT_FALSE
    reference-EXPECT_FALSE

    reference-FAIL
    reference-FATALLY_FAIL

    reference-TEST_CASE
    reference-DONT_TEST_CASE
    reference-MUST_TEST_CASE

    reference-TEST_SUITE
    reference-DONT_TEST_SUITE
    reference-MUST_TEST_SUITE
)
    addSimpleExample(${simple-example-name})
endforeach(simple-example-name)
#@-others
#@-<< Tests >>

add_custom_target(tests DEPENDS ${tests-dependencies})
#@-leo
