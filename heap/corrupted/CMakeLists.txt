#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex3-corrupted
  VERSION     0.0 # n.n[.n[.n]]
  DESCRIPTION "Example of corruption on the heap"
  LANGUAGES   C CXX
  )

#-------------------------------------------------------------------------------
# Find project directory containing local cmake modules and
# in particular, the project_defaults.cmake file
#...............................................................................
set( defaults "project_defaults" )
set( _dir "${CMAKE_CURRENT_SOURCE_DIR}" )
cmake_path( GET _dir ROOT_PATH _root )
while( NOT EXISTS "${_dir}/cmake/${defaults}.cmake" )
  cmake_path( GET _dir PARENT_PATH _dir )
  if( "${_dir}" STREQUAL "${_root}" )
    message( FATAL_ERROR "Unable to find project working tree directory!" )
  endif()
endwhile()
set( WORKTREE_DIR "${_dir}" CACHE PATH "Contains cmake/${defaults}.cmake" )
list( PREPEND CMAKE_MODULE_PATH "${WORKTREE_DIR}/cmake" )
include( "${defaults}" )

#-------------------------------------------------------------------------------
# Packages
#...............................................................................
find_package( fmt REQUIRED )

#-------------------------------------------------------------------------------
# Executables
#...............................................................................
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

#-------------------------------------------------------------------------------
# vim:syntax=cmake:nospell
