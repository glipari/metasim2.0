# Add include directories
include_directories(.)
include_directories(../src)

# Create Catch library to decrease compile times
add_library(TestMain STATIC TestMain.cpp)

# Create the executable.
add_executable(TestEntityOrder myentity.cpp TestEntityOrder.cpp)
add_executable(TestEntitySameName myentity.cpp TestEntitySameName.cpp)
add_executable(TestParseUtil TestParseUtil.cpp)
add_executable(TestTick TestTick.cpp)
add_executable(TestRandomVar TestRandomVar.cpp)
add_executable(TestFactory TestFactory.cpp)

target_compile_features(TestEntityOrder PRIVATE cxx_range_for)
target_compile_features(TestEntitySameName PRIVATE cxx_range_for)
target_compile_features(TestParseUtil PRIVATE cxx_range_for)
target_compile_features(TestTick PRIVATE cxx_range_for)
target_compile_features(TestRandomVar PRIVATE cxx_range_for)
target_compile_features(TestFactory PRIVATE cxx_range_for)

# Indicate that rtlib need metasim library.
target_link_libraries(TestEntityOrder TestMain metasim)
target_link_libraries(TestEntitySameName TestMain metasim)
target_link_libraries(TestParseUtil TestMain metasim)
target_link_libraries(TestTick TestMain metasim)
target_link_libraries(TestRandomVar TestMain metasim)
target_link_libraries(TestFactory TestMain metasim)

# Add tests for CTest
add_test (NAME TestEntityOrder COMMAND TestEntityOrder)
add_test (NAME TestEntitySameName COMMAND TestEntitySameName)
add_test (NAME TestParseUtil COMMAND TestParseUtil)
add_test (NAME TestTick COMMAND TestTick)
add_test (NAME TestRandomVar COMMAND TestRandomVar)
add_test (NAME TestFactory COMMAND TestFactory)

