# Add include directories
include_directories (.)

# Create a library called "metasim" which includes the source files.
add_library (${PROJECT_NAME} ${LIBRARY_TYPE} basestat.cpp entity.cpp genericvar.cpp
    regvar.cpp strtoken.cpp trace.cpp debugstream.cpp event.cpp
    randomvar.cpp simul.cpp tick.cpp)

target_compile_features (${PROJECT_NAME} PRIVATE cxx_range_for)

# Export.
export (TARGETS ${PROJECT_NAME} FILE "./metasimConfig.cmake")
export (PACKAGE ${PROJECT_NAME})
  
