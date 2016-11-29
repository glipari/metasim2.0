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

# Create the executable.
add_executable(TestEntityOrder TestMain.cpp myentity.cpp TestEntityOrder.cpp)
add_executable(TestEntitySameName TestMain.cpp myentity.cpp TestEntitySameName.cpp)
add_executable(TestParseUtil TestMain.cpp TestParseUtil.cpp)
add_executable(TestTick TestMain.cpp TestTick.cpp)
add_executable(TestRandomVar TestMain.cpp TestRandomVar.cpp)
add_executable(TestFactory TestMain.cpp TestFactory.cpp)

# Indicate that rtlib need metasim library.
target_link_libraries(TestEntityOrder metasim)
target_link_libraries(TestEntitySameName metasim)
target_link_libraries(TestParseUtil metasim)
target_link_libraries(TestTick metasim)
target_link_libraries(TestRandomVar metasim)
target_link_libraries(TestFactory metasim)

# Add tests for CTest
add_test (NAME TestEntityOrder COMMAND TestEntityOrder)
add_test (NAME TestEntitySameName COMMAND TestEntitySameName)
add_test (NAME TestParseUtil COMMAND TestParseUtil)
add_test (NAME TestTick COMMAND TestTick)
add_test (NAME TestRandomVar COMMAND TestRandomVar)
add_test (NAME TestFactory COMMAND TestFactory)

