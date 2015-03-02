cmake_minimum_required(VERSION 2.8.12)

project(Programmation3D)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lGL -lglut -lGLU ${CMAKE_CXX_FLAGS}")

set(CORE_FILES
src/core/Point.cpp
src/core/Vector.cpp
src/core/Vector.hpp
src/core/Point.hpp
src/core/Axis.hpp
src/core/Axis.cpp
src/core/Curve.hpp
src/core/Curve.cpp
)
set(CURVE_FILES
src/curves/HermiteCubicCurve.hpp
src/curves/HermiteCubicCurve.cpp
src/curves/BezierCurve.cpp
src/curves/BezierCurve.hpp
src/curves/BernsteinBezierCurve.hpp
src/curves/BernsteinBezierCurve.cpp
src/curves/DeCasteljauBezierCurve.hpp
src/curves/DeCasteljauBezierCurve.cpp
)

set(SURFACE_FILES
src/surfaces/Surface.hpp
src/surfaces/Surface.cpp
src/surfaces/CylindricSurface.hpp
src/surfaces/CylindricSurface.cpp
src/surfaces/BezierSurface.hpp
src/surfaces/BezierSurface.cpp
src/surfaces/RuledSurface.hpp
src/surfaces/RuledSurface.cpp
)

set(PRIMITIVE_FILES
src/primitives/Cylinder.cpp
src/primitives/Cylinder.hpp
)


add_executable(Programmation3D ${CORE_FILES} ${CURVE_FILES} src/tp/TP_OPENGL.cpp)

add_executable(tp3.out ${CORE_FILES} ${CURVE_FILES} ${PRIMITIVES_FILES} src/tp3/tp3.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(Programmation3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )