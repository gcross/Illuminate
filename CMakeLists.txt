#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1276: * @thin CMakeLists.txt
cmake_minimum_required (VERSION 2.6)
project (Illuminate)

if( NOT CMAKE_BUILD_TYPE )
set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif ()

message (STATUS "Build type is " ${CMAKE_BUILD_TYPE})

include_directories ("includes")
add_subdirectory ("includes")
add_subdirectory ("sources")
add_subdirectory ("tests")
#@-leo
