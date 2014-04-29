#Checking CMake version#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#Setting the project name
project("RobotEscape")

#set the source files and path 
set(SOURCES src/Main.cpp src/Camera.cpp src/Camera.h src/BoundingBox.cpp src/BoundingBox.h src/GameAsset.cpp src/GameAsset.h src/CubeAsset.h src/CubeAsset.cpp src/Player.h src/Player.cpp src/InputHandler.h src/InputHandler.cpp)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Modules)


#Checking all packages are installed
#First OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#GLU library
if(NOT OPENGL_GLU_FOUND)
    message(ERROR " GLU not found!")
endif(NOT OPENGL_GLU_FOUND)
#SDL2 library
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(ERROR " SDL2 not found!")
endif(NOT SDL2_FOUND)
#GLU library
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
	message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)
#Vectormath library
#find_package(VECTORMATH REQUIRED)
#if(NOT VECTORMATH_FOUND)
#	message(ERROR " Vectormath not found!")
#endif(NOT VECTORMATH_FOUND)

#Include directories 
include_directories(${SDL2_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})  #${Vectormath_INCLUDE_DIRS}
#Linker directories
link_directories(${SDL2_LIBRARY_DIRS} ${OpenGL_LIBRARY_DIRS}) #${Vectormath_LIBRARY_DIRS}
#Definitions 
add_definitions(${SDL_DEFINITIONS} ${OpenGL_DEFINITIONS}) #${Vectormath_DEFINITIONS}

#Compiler flags depending on the OS 
if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g")
endif(UNIX)

#Define the c++ version used 
add_definitions("-std=c++0x")

#setting and linking the libraries
set(LIBS ${LIBS} ${SDL2_LIBRARY} ${OpenGL_LIBRARY} ${GLEW_LIBRARY}) #${Vectormath_LIBRARIES}
link_libraries(${LIBS})

#Create the executable file 
add_executable(RobotEscape ${SOURCES})

### LINKER ###
target_link_libraries(RobotEscape GL GLU GLEW SDL2)