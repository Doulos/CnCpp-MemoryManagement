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

add_executable( usingnames )
target_sources( usingnames PRIVATE usingnames.cpp )
add_test(       NAME usingnames COMMAND usingnames )

# vim:syntax=cmake:nospell
