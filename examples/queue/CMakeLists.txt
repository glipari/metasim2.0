# Add include directories
include_directories(.)
include_directories(../../src)

# Create the executable.
add_executable(queue queue.cpp queue.hpp)

target_compile_features(queue PRIVATE cxx_range_for)

# Indicate that the executable needs metasim library.
target_link_libraries( queue metasim )
