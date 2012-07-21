cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (Illuminate CXX)
set (version 1.0)

# Settings {{{
# Offline HTML {{{
set (OFFLINE_HTML
    NO
    CACHE BOOL
    "If true, then ensures that HTML documentation can be viewed offline."
    )

if(${OFFLINE_HTML})
    set(USE_MATHJAX NO)
else(${OFFLINE_HTML})
    set(USE_MATHJAX YES)
endif(${OFFLINE_HTML})
# }}}
# Version Prefix {{{
set (INSTALL_IN_VERSIONED_SUBDIRECTORY
    NO
    CACHE BOOL
    "If true, the installation directories are appended by a subdirectory labeled by the version number."
    )

if(${INSTALL_IN_VERSIONED_SUBDIRECTORY})
    set(LIBRARY_INSTALLATION_DIRECTORY lib/Illuminate-${version})
    set(HEADER_INSTALLATION_DIRECTORY include/illuminate-${version})
else(${INSTALL_IN_VERSIONED_SUBDIRECTORY})
    set(LIBRARY_INSTALLATION_DIRECTORY lib)
    set(HEADER_INSTALLATION_DIRECTORY include)
endif(${INSTALL_IN_VERSIONED_SUBDIRECTORY})
# }}}
# }}}

ENABLE_TESTING()

# Configure target output paths {{{
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
# }}}

# Configure Boost {{{
find_package( Boost 1.42 COMPONENTS serialization system thread program_options REQUIRED )
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )
# }}}

if( NOT CMAKE_BUILD_TYPE )
set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif ()

message (STATUS "Build type is " ${CMAKE_BUILD_TYPE})

include_directories ("includes")

add_subdirectory ("examples")
add_subdirectory ("includes")
add_subdirectory ("package")
add_subdirectory ("sources")

# Configure documentation {{{
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
# }}}
