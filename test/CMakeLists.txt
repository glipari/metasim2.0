# Add include directory
include_directories(.)
include_directories(../src/)

# Environment-based settings.
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
elseif(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
elseif(WIN32)

endif()

# Create Catch library to decrease compile times
add_library(TestMain STATIC TestMain.cpp)

# Create the executable.
add_executable(TestEntityOrder myentity.cpp TestEntityOrder.cpp)
add_executable(TestEntitySameName myentity.cpp TestEntitySameName.cpp)
add_executable(TestParseUtil TestParseUtil.cpp)
add_executable(TestTick TestTick.cpp)
add_executable(TestRandomVar TestRandomVar.cpp)

# Indicate that rtlib need metasim library.
target_link_libraries(TestEntityOrder TestMain metasim)
target_link_libraries(TestEntitySameName TestMain metasim)
target_link_libraries(TestParseUtil TestMain metasim)
target_link_libraries(TestTick TestMain metasim)
target_link_libraries(TestRandomVar TestMain metasim m)

# Add tests for CTest
add_test (NAME TestEntityOrder COMMAND TestEntityOrder)
add_test (NAME TestEntitySameName COMMAND TestEntitySameName)
add_test (NAME TestParseUtil COMMAND TestParseUtil)
add_test (NAME TestTick COMMAND TestTick)
add_test (NAME TestRandomVar COMMAND TestRandomVar)

#add_executable(test_metasim myentity.cpp TestEntityOrder.cpp
#  TestEntitySameName.cpp TestParseUtil.cpp TestTick.cpp
#  TestRandomVar.cpp)
#target_link_libraries(test_metasim metasim)
