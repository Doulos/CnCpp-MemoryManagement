#!cmake .
#
# See $ENV{APPS}/cmake/ABOUT_CMAKE.md for more information.

cmake_minimum_required( VERSION 3.11 )

project(      ex1-overlooked
  VERSION     0.0 # n.n[.n[.n]]
  DESCRIPTION "Resource information"
  LANGUAGES   CXX
  )
list( PREPEND CMAKE_MODULE_PATH "$ENV{PROJECT_DIR}/cmake" )
include( project_defaults )

# Packages as needed
find_package( fmt REQUIRED )

add_executable(             ex1-overlooked )
target_sources(             ex1-overlooked PRIVATE ex1-overlooked.cpp )
target_link_libraries(      ex1-overlooked PRIVATE fmt::fmt )
add_test(                   ex1-overlooked ex1-overlooked )

add_executable(             rinfo )
target_sources(             rinfo PRIVATE rinfo.cpp )
target_compile_definitions( rinfo PRIVATE SELFTEST_RINFO )
target_link_libraries(      rinfo PRIVATE fmt::fmt )
add_test(                   rinfo rinfo )

# vim:syntax=cmake:nospell
