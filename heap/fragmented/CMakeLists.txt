#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex2-fragmented
  VERSION     1.0
  DESCRIPTION "Exploration of heap fragmentation"
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
# Packages for this project
#...............................................................................
find_package( fmt REQUIRED )

#-------------------------------------------------------------------------------
# Executables
#...............................................................................
add_executable( memusage )
target_sources( memusage PRIVATE memusage.cpp )
target_compile_definitions( memusage PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD> SELFTEST_MEMUSAGE)
target_link_libraries(      memusage PRIVATE fmt::fmt )
add_test( NAME memusage COMMAND memusage )

add_executable( rssusage )
target_sources( rssusage PRIVATE rssusage.h rssusage.c rssusage.cpp )
target_compile_definitions( rssusage PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD> )
target_link_libraries(      rssusage PRIVATE fmt::fmt )
add_test( NAME rssusage COMMAND rssusage )

add_executable( pool )
target_sources( pool PRIVATE pool.hpp pool.cpp )
target_compile_definitions( pool PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD> )
target_link_libraries(      pool PRIVATE fmt::fmt )
add_test( NAME pool COMMAND pool )

#-------------------------------------------------------------------------------
# vim:syntax=cmake:nospell
