cmake_minimum_required(VERSION 2.8.12)

project(Programmation3D)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lGL -lglut -lGLU ${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES src/tp/TP_OPENGL.cpp
src/core/Point.cpp
src/core/Vector.cpp
src/core/Vector.hpp
src/core/Point.hpp
src/core/Axis.hpp
src/core/Curve.hpp
src/core/Curve.cpp
src/core/HermiteCubicCurve.hpp
src/core/HermiteCubicCurve.cpp
src/core/BernsteinBezierCurve.hpp
src/core/BernsteinBezierCurve.cpp
)
add_executable(Programmation3D ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Programmation3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )