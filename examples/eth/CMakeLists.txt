# Add include directories
include_directories(.)
include_directories(../../src)

# Create the executable.
add_executable(eth example.cpp link.cpp	link.hpp message.cpp message.hpp netinterface.cpp
	netinterface.hpp node.cpp node.hpp)

target_compile_features(eth PRIVATE cxx_range_for)

# Indicate that the executable needs metasim library.
target_link_libraries( eth metasim )
