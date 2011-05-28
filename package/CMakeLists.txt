#@+leo-ver=5-thin
#@+node:gcross.20110527192131.2326: * @file CMakeLists.txt
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Illuminate-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/Illuminate-config.cmake @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Illuminate-config-version.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/Illuminate-config-version.cmake @ONLY
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/Illuminate-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Illuminate-config-version.cmake
    DESTINATION
        lib/Illuminate-${version}
)

install (
    EXPORT Illuminate-targets
    DESTINATION lib/Illuminate-${version}
)
#@-leo
