#!cmake .

cmake_minimum_required( VERSION 3.21 )

project( stack VERSION 1.0 DESCRIPTION "Exploration of stack" LANGUAGES C CXX )

#-------------------------------------------------------------------------------
# Find project directory containing defaults
#-------------------------------------------------------------------------------
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

#include( stackusage )

# Packages for this project
find_package( fmt REQUIRED )
#-------------------------------------------------------------------------------
# C code examples from slides
set_target( "stack-c" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE stack.c)
add_test( NAME test-"${Target}" COMMAND "${Target}" )

#-------------------------------------------------------------------------------
# C++ (modern) examples from slides
set_target( "stack-cpp" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE stack.cpp)
#target_compile_options()
target_link_libraries( "${Target}" PRIVATE fmt::fmt )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

message( NOTICE "Targets=${Targets}" )

# vim:syntax=cmake:nospell
