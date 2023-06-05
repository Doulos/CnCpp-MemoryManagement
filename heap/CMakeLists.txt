cmake_minimum_required( VERSION 3.21 )

project(      heap
  VERSION     1.0
  DESCRIPTION "Examples on heap management from the slides"
  LANGUAGES   C CXX
  )

#-------------------------------------------------------------------------------
# Find project directory containing local cmake modules and
# in particular, the project_defaults.cmake file
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

# Packages for this project
find_package( fmt REQUIRED )

#-------------------------------------------------------------------------------
# C code examples from slides
set_target( "heap-c" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE heap.c)
add_test( NAME test-"${Target}" COMMAND "${Target}" )

#-------------------------------------------------------------------------------
# C++ (modern) examples from slides
set_target( "heap-cpp" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE heap.cpp)
target_link_libraries( "${Target}" PRIVATE fmt::fmt )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

#-------------------------------------------------------------------------------
# Other useful examples
set_target( "free-ptr" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE freePtr.c )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

set_target( "delete-ptr" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE deletePtr.cpp)
target_link_libraries( "${Target}" PRIVATE fmt::fmt )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

set_target( "unique-ptr" )
add_executable( "${Target}" )
target_sources( "${Target}" PRIVATE uniquePtr.cpp)
target_link_libraries( "${Target}" PRIVATE fmt::fmt )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

set_target( "heapusage" )
add_executable( "${Target}" )
target_sources( "${Target}" PUBLIC heapusage.hpp PRIVATE heapusage.cpp)
target_link_libraries( "${Target}" PRIVATE fmt::fmt )
target_compile_definitions( "${Target}" PRIVATE SELFTEST_HEAPUSAGE=1 )
add_test( NAME test-"${Target}" COMMAND "${Target}" )

add_subdirectory( corrupted )
add_subdirectory( fragmented )
add_subdirectory( overlooked )

# vim:syntax=cmake:nospell
