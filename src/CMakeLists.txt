# Add defs for the compiler
if(UNIX)
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
   #Add current directory
	include_directories(.)

	# Create a library called "metasim" which includes the source files.
	# The extension is already found. Any number of sources could be listed here.
	add_library(metasim SHARED basestat.cpp entity.cpp genericvar.cpp
	  regvar.cpp strtoken.cpp trace.cpp debugstream.cpp event.cpp
  randomvar.cpp simul.cpp tick.cpp)
  
elseif(WINDOWS)
   #Add current directory
	include_directories(.)

	# Create a library called "metasim" which includes the source files.
	# The extension is already found. Any number of sources could be listed here.
	add_library(metasim STATIC basestat.cpp entity.cpp genericvar.cpp
	  regvar.cpp strtoken.cpp trace.cpp debugstream.cpp event.cpp
  randomvar.cpp simul.cpp tick.cpp)  
endif()



