#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1276: * @file CMakeLists.txt
cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (Illuminate CXX)
set (version 1.0)

#@+<< Configure target output paths >>
#@+node:gcross.20110430202346.1607: ** << Configure target output paths >>
set (LIBRARY_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/lib
    CACHE PATH
    "Single directory for all libraries."
    )

set (EXECUTABLE_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables."
    )

mark_as_advanced(
    LIBRARY_OUTPUT_PATH
    EXECUTABLE_OUTPUT_PATH
    )
#@-<< Configure target output paths >>

#@+<< Configure Boost >>
#@+node:gcross.20110430202346.1609: ** << Configure Boost >>
SET(Boost_ADDITIONAL_VERSIONS "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0")
find_package( Boost COMPONENTS thread program_options REQUIRED )
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )
#@-<< Configure Boost >>

if( NOT CMAKE_BUILD_TYPE )
set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif ()

message (STATUS "Build type is " ${CMAKE_BUILD_TYPE})

include_directories ("includes")

add_subdirectory ("includes")
add_subdirectory ("package")
add_subdirectory ("sources")
add_subdirectory ("tests")

#@+<< Configure documentation >>
#@+node:gcross.20110430202346.1610: ** << Configure documentation >>
# add a target to generate API documentation with Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
#@-<< Configure documentation >>
#@-leo
