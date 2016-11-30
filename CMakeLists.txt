cmake_minimum_required (VERSION 3.1)
project (metasim)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# Include dirs.
add_subdirectory (src)
add_subdirectory (examples)

enable_testing(true)
add_subdirectory (test)

