# Add include directories
include_directories(.)
include_directories(../../src)

# Create the executable.
add_executable(markov markov.cpp)

target_compile_features(markov PRIVATE cxx_range_for)

# Indicate that the executable needs metasim library.
target_link_libraries( markov metasim )
