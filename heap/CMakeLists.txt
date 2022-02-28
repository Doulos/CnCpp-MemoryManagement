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
set( TARGET "heap-c" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PRIVATE heap.c)
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

#-------------------------------------------------------------------------------
# C++ (modern) examples from slides
set( TARGET "heap-cpp" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PRIVATE heap.cpp)
target_link_libraries( "${TARGET}" PRIVATE fmt::fmt )
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

#-------------------------------------------------------------------------------
# Other useful examples
set( TARGET "free-ptr" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PRIVATE freePtr.c )
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

set( TARGET "delete-ptr" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PRIVATE deletePtr.cpp)
target_link_libraries( "${TARGET}" PRIVATE fmt::fmt )
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

set( TARGET "unique-ptr" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PRIVATE uniquePtr.cpp)
target_link_libraries( "${TARGET}" PRIVATE fmt::fmt )
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

set( TARGET "heapusage" )
add_executable( "${TARGET}" )
target_sources( "${TARGET}" PUBLIC heapusage.hpp PRIVATE heapusage.cpp)
target_link_libraries( "${TARGET}" PRIVATE fmt::fmt )
target_compile_definitions( "${TARGET}" PRIVATE SELFTEST_HEAPUSAGE=1 )
add_test( NAME test-"${TARGET}" COMMAND "${TARGET}" )

# vim:syntax=cmake:nospell
