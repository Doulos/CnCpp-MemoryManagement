#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex2-fragmented
  VERSION     1.0
  DESCRIPTION "Exploration of heap fragmentation"
  LANGUAGES   C CXX
  )

list( PREPEND CMAKE_MODULE_PATH "$ENV{PROJECT_DIR}/cmake" )
include( project_defaults )

# Packages for this project
find_package( fmt REQUIRED )

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

# vim:syntax=cmake:nospell
