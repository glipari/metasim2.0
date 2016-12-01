# Add include directories
include_directories(.)

# Create a library called "metasim" which includes the source files.
add_library(metasim STATIC basestat.cpp entity.cpp genericvar.cpp
  regvar.cpp strtoken.cpp trace.cpp debugstream.cpp event.cpp
  randomvar.cpp simul.cpp tick.cpp)

target_compile_features(metasim PRIVATE cxx_range_for)

# Export.
export(TARGETS metasim FILE "./metasimConfig.cmake")
export(PACKAGE metasim)
