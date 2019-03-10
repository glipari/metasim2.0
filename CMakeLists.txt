cmake_minimum_required (VERSION 3.1)
project (metasim)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") 
set(CMAKE_CXX_STANDARD 14) 

set(LIBRARY_TYPE STATIC)

# Include dirs.
add_subdirectory (src)
add_subdirectory (examples)

enable_testing (true)
add_subdirectory (test)
