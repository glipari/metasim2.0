# Add include directories
include_directories (.)
include_directories (../src)

set (METASIM_TEST_LIBRARY ${PROJECT_NAME}_test)

# Create Catch library to decrease compile times
add_library (${METASIM_TEST_LIBRARY} ${LIBRARY_TYPE} TestMain.cpp)

# Define a macro to simplify tests creation
function (create_test name)
    add_executable (${name} ${ARGN})
    target_compile_features (${name} PRIVATE cxx_range_for)
    target_link_libraries (${name} ${METASIM_TEST_LIBRARY} ${PROJECT_NAME})
    add_test (NAME ${name} COMMAND ${name})
endfunction (create_test)

create_test (TestEntityOrder myentity.cpp TestEntityOrder.cpp)
create_test (TestEntitySameName myentity.cpp TestEntitySameName.cpp)
create_test (TestParticle myentity.cpp TestParticle.cpp)
create_test (TestParseUtil TestParseUtil.cpp)
create_test (TestTick TestTick.cpp)
create_test (TestRandomVar TestRandomVar.cpp)
create_test (TestFactory TestFactory.cpp)
create_test (TestStat TestStat.cpp)
create_test (TestHistory TestHistory.cpp)
