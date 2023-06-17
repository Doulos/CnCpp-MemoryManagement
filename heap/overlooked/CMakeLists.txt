#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex1-overlooked
  VERSION     0.0 # n.n[.n[.n]]
  DESCRIPTION "Resource information"
  LANGUAGES   CXX
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
# Packages as needed
#...............................................................................
find_package( fmt REQUIRED )

#-------------------------------------------------------------------------------
# Executables
#...............................................................................
add_executable(             ex1-overlooked )
target_sources(             ex1-overlooked PRIVATE ex1-overlooked.cpp )
target_link_libraries(      ex1-overlooked PRIVATE fmt::fmt )
add_test(                   ex1-overlooked ex1-overlooked )

add_executable(             rinfo )
target_sources(             rinfo PRIVATE rinfo.cpp )
target_compile_definitions( rinfo PRIVATE SELFTEST_RINFO )
target_link_libraries(      rinfo PRIVATE fmt::fmt )
add_test(                   rinfo rinfo )

#-------------------------------------------------------------------------------
# vim:syntax=cmake:nospell
