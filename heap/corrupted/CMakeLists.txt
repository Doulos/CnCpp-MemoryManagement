#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex3-corrupted
  VERSION     0.0 # n.n[.n[.n]]
  DESCRIPTION "Example of corruption on the heap"
  LANGUAGES   C CXX
  )
list( PREPEND CMAKE_MODULE_PATH "$ENV{PROJECT_DIR}/cmake" )
include( project_defaults )

# Packages
find_package( fmt REQUIRED )

add_executable( corrupt-c )
target_sources( corrupt-c PRIVATE corrupt.c )
target_compile_definitions( corrupt-c PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD> )
add_test( NAME corrupt0 COMMAND corrupt-c    )
add_test( NAME corrupt1 COMMAND corrupt-c  1 )
add_test( NAME corrupt2 COMMAND corrupt-c -1 )

add_executable( checking-cpp )
target_sources( checking-cpp PRIVATE checking.cpp )
target_compile_definitions( checking-cpp PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD> )
add_test( NAME checking-cpp COMMAND checking-cpp )

install( TARGETS corrupt-c CONFIGURATIONS Debug DESTINATION $ENV{SUBPROJ_DIR} )
install( TARGETS checking-cpp CONFIGURATIONS Debug DESTINATION $ENV{SUBPROJ_DIR} )

# vim:syntax=cmake:nospell
