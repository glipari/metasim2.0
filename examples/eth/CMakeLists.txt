# Add include directories
include_directories (.)
include_directories (../../src)

set (EXECUTABLE_NAME eth)
set (EXECUTABLE_SOURCES example.cpp link.cpp link.hpp message.cpp message.hpp
    netinterface.cpp netinterface.hpp node.cpp node.hpp)

# Create the executable.
add_executable (${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

target_compile_features (${EXECUTABLE_NAME} PRIVATE cxx_range_for)
#target_compile_options(${EXECUTABLE_NAME} PRIVATE -g -fsanitize=address)

# Indicate that the executable needs metasim library.
target_link_libraries (${EXECUTABLE_NAME} ${PROJECT_NAME})
#target_link_libraries (${EXECUTABLE_NAME} ${PROJECT_NAME} -fsanitize=address)
