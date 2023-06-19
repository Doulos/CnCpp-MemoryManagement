#!cmake .

cmake_minimum_required( VERSION 3.21 )

project( memmanage VERSION 6.1 DESCRIPTION "C/C++ Memory Management" LANGUAGES CXX )

#-------------------------------------------------------------------------------
# Find project directory containing defaults
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
# Exercise specific
enable_testing()
add_subdirectory( heap )
add_subdirectory( stack )

