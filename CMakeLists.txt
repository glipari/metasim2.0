cmake_minimum_required (VERSION 2.6)
project (metasim)

# include dirs
add_subdirectory (src)
add_subdirectory (examples)
add_subdirectory (test)

#export
export(TARGETS metasim FILE "./metasimConfig.cmake")
export(PACKAGE metasim)


