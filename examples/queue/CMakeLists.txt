# Add include directories
include_directories (.)
include_directories (../../src)

#set (EXECUTABLE_NAME main_step)
#set (EXECUTABLE_SOURCES queue.cpp main_step.cpp)

# Create the executable.
#add_executable (${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

add_executable (main_step queue.cpp main_step.cpp)
add_executable (main queue.cpp main.cpp)

#target_compile_features (${EXECUTABLE_NAME} PRIVATE cxx_range_for)

# Indicate that the executable needs metasim library.
target_link_libraries (main ${PROJECT_NAME})
target_link_libraries (main_step ${PROJECT_NAME})
