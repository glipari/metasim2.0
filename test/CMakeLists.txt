# Add include directories
include_directories (.)
include_directories (../src)

set (METASIM_TEST_LIBRARY ${PROJECT_NAME}_test)

# Create Catch library to decrease compile times
add_library (${METASIM_TEST_LIBRARY} ${LIBRARY_TYPE} TestMain.cpp)

# Define a macro to simplify tests creation
macro (create_test name)
    target_compile_features (${name} PRIVATE cxx_range_for)
    target_link_libraries (${name} ${METASIM_TEST_LIBRARY} ${PROJECT_NAME})
    add_test (NAME ${name} COMMAND ${name})
endmacro (create_test)

add_executable (TestEntityOrder myentity.cpp TestEntityOrder.cpp)
create_test (TestEntityOrder myentity.cpp TestEntityOrder.cpp)

add_executable (TestEntitySameName myentity.cpp TestEntitySameName.cpp)
create_test (TestEntitySameName)

add_executable (TestParticle myentity.cpp TestParticle.cpp)
create_test (TestParticle)

add_executable (TestParseUtil TestParseUtil.cpp)
create_test (TestParseUtil)

add_executable (TestTick TestTick.cpp)
create_test (TestTick)

add_executable (TestRandomVar TestRandomVar.cpp)
create_test (TestRandomVar)

add_executable (TestFactory TestFactory.cpp)
create_test (TestFactory)
