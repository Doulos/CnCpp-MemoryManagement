cmake_minimum_required( VERSION 3.21 )

project(      heap
  VERSION     1.0
  DESCRIPTION "Examples on heap management from the slides"
  LANGUAGES   C CXX
  )

list( PREPEND CMAKE_MODULE_PATH "$ENV{PROJECT_DIR}/cmake" )
include( project_defaults )

# Packages for this project
find_package( fmt REQUIRED )

#-------------------------------------------------------------------------------
# C code examples from slides
set( EXAMPLE "heap-c" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PRIVATE heap.c)
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

#-------------------------------------------------------------------------------
# C++ (modern) examples from slides
set( EXAMPLE "heap-cpp" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PRIVATE heap.cpp)
target_link_libraries( "${EXAMPLE}" PRIVATE fmt::fmt )
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

#-------------------------------------------------------------------------------
# Other useful examples
set( EXAMPLE "free-ptr" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PRIVATE freePtr.c )
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

set( EXAMPLE "delete-ptr" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PRIVATE deletePtr.cpp)
target_link_libraries( "${EXAMPLE}" PRIVATE fmt::fmt )
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

set( EXAMPLE "unique-ptr" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PRIVATE uniquePtr.cpp)
target_link_libraries( "${EXAMPLE}" PRIVATE fmt::fmt )
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

set( EXAMPLE "heapusage" )
add_executable( "${EXAMPLE}" )
target_sources( "${EXAMPLE}" PUBLIC heapusage.hpp PRIVATE heapusage.cpp)
target_link_libraries( "${EXAMPLE}" PRIVATE fmt::fmt )
target_compile_definitions( "${EXAMPLE}" PRIVATE SELFTEST_HEAPUSAGE=1 )
add_test( NAME test-"${EXAMPLE}" COMMAND "${EXAMPLE}" )

# vim:syntax=cmake:nospell
