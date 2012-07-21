configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/IlluminateConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/IlluminateConfig.cmake @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/IlluminateConfig-version.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/IlluminateConfig-version.cmake @ONLY
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/IlluminateConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/IlluminateConfig-version.cmake
    DESTINATION
        lib/Illuminate-${version}
)

install (
    EXPORT Illuminate-targets
    DESTINATION lib/Illuminate-${version}
)
