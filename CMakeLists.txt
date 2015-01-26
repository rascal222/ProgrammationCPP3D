cmake_minimum_required(VERSION 2.8.12)

project(Programmation3D)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lGL -lglut ${CMAKE_CXX_FLAGS}")
set(SOURCE_FILES src/tp/test.cpp
src/core/Point.cpp
src/core/Vector.cpp
)
add_executable(Programmation3D ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Programmation3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )