# Add include directories
include_directories (.)

set(SOURCE_FILES
  basestat.cpp
  debugstream.cpp
  entity.cpp
  event.cpp
  genericvar.cpp
  randomvar.cpp
  regvar.cpp
  simul.cpp
  strtoken.cpp
  tick.cpp
  trace.cpp)

set(HEADER_FILES
  baseexc.hpp
  basestat.hpp
  basetype.hpp
  cloneable.hpp
  debugstream.hpp
  entity.hpp
  event.hpp
  factory.hpp
  genericvar.hpp
  gevent.hpp
  history.hpp
  metasim.hpp
  particle.hpp
  plist.hpp
  randomvar.hpp
  regvar.hpp
  simul.hpp
  strtoken.hpp
  tick.hpp
  trace.hpp)

# Create a library called "metasim" which includes the source files.
add_library (${PROJECT_NAME} ${LIBRARY_TYPE} ${SOURCE_FILES})

target_compile_features (${PROJECT_NAME} PRIVATE cxx_range_for)

# Export.
export (TARGETS ${PROJECT_NAME} FILE "./metasimConfig.cmake")
export (PACKAGE ${PROJECT_NAME})
install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)
