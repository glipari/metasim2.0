cmake_minimum_required (VERSION 3.1)
project (metasim)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-D__DEBUG__)
  message("Debug added as a compilation flag")
endif()

set(LIBRARY_TYPE STATIC)

# Include dirs.
add_subdirectory (src)
add_subdirectory (examples)

enable_testing (true)
add_subdirectory (test)
