cmake_minimum_required (VERSION 2.6)
project (metasim)

# Set compile optimization flags
SET(CMAKE_CXX_FLAGS "-Ofast")
SET(CMAKE_C_FLAGS "-Ofast")

# Include dirs.
add_subdirectory (src)
add_subdirectory (examples)

enable_testing(true)
add_subdirectory (test)
