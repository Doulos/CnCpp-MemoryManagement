
# Generate map file
if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
  target_link_options( memusage PRIVATE "-Wl,-fstack-usage,-Map=output.map" )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  target_link_options( memusage PRIVATE "-Wl,-map,output.map" )
endif()

