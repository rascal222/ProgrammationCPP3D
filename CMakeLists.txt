cmake_minimum_required(VERSION 3.1.3)

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
src/core/PolarPoint.hpp
src/core/PolarPoint.cpp
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

set(GLWRAPPER_FILES
src/glWrappers/GLCoreRendering.cpp
src/glWrappers/GlCoreRendering.hpp
src/glWrappers/Camera.cpp
src/glWrappers/Camera.hpp
src/glWrappers/EulerCamera.cpp
src/glWrappers/EulerCamera.hpp
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
src/surfaces/SurfacicSquare.cpp
src/surfaces/SurfacicSquare.hpp
)

set(PRIMITIVE_FILES
src/primitives/Cylinder.cpp
src/primitives/Cylinder.hpp
src/primitives/Cone.cpp
src/primitives/Cone.hpp
src/primitives/Disc.cpp
src/primitives/Disc.hpp
src/primitives/Sphere.cpp
src/primitives/Sphere.hpp
src/primitives/Voxel.cpp
src/primitives/Voxel.hpp
src/primitives/Shape.cpp
src/primitives/Shape.hpp
)

set(OCTREE_FILES
src/octree/AdaptativeOctree.cpp
src/octree/AdaptativeOctree.hpp
src/octree/TwoShapeAdaptiveOctree.cpp
src/octree/TwoShapeAdaptiveOctree.hpp
src/octree/IntersectAdaptiveOctree.cpp
src/octree/IntersectAdaptiveOctree.hpp
src/octree/DivideAdaptiveOctree.hpp
src/octree/DivideAdaptiveOctree.cpp
src/octree/UnionAdaptiveOctree.cpp
src/octree/UnionAdaptiveOctree.hpp
)

set(MESHING_FILES
src/meshing/IdTriangle.hpp
src/meshing/IdTriangle.cpp
src/meshing/OffManipulator.cpp
src/meshing/offManipulator.hpp
src/meshing/Mesh.cpp
src/meshing/Mesh.hpp
)

add_executable(Tp2 ${CORE_FILES} ${CURVE_FILES} ${GLWRA²    PPER_FILES} src/tp/TP_OPENGL.cpp)
add_executable(Tp3-drawCylinder ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${GLWRAPPER_FILES} src/tp3/mainCylindricSurface.cpp)
add_executable(Tp3-drawRuledSurface ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${GLWRAPPER_FILES} src/tp3/mainRuledSurf.cpp)
add_executable(Tp3-drawSurfacicSquare ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${GLWRAPPER_FILES} src/tp3/tp3.cpp)
add_executable(Tp4-drawCone ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES} src/tp4/mainCone.cpp)
add_executable(Tp4-drawCylinder ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES} src/tp4/mainCylinder.cpp)
add_executable(Tp4-drawSphere ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES} src/tp4/mainSphere.cpp)
add_executable(Tp5-drawVoxelSphere ${OCTREE_FILES} ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES}  src/tp5/voxel.cpp)
add_executable(Tp5-drawVoxelCylinder ${OCTREE_FILES} ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES}  src/tp5/mainCylinder.cpp)
add_executable(Tp5-drawIntercept ${OCTREE_FILES} ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES}  src/tp5/mainIntersect.cpp)
add_executable(Tp5-drawDivide ${OCTREE_FILES} ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES}  src/tp5/mainDivide.cpp)
add_executable(Tp5-drawUnions ${OCTREE_FILES} ${CORE_FILES} ${CURVE_FILES} ${SURFACE_FILES} ${PRIMITIVE_FILES} ${GLWRAPPER_FILES}  src/tp5/mainUnion.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(Tp2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp3-drawCylinder ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp3-drawRuledSurface ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp3-drawSurfacicSquare ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp4-drawCylinder ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp4-drawCone ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp4-drawSphere ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp5-drawVoxelSphere ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp5-drawVoxelCylinder ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp5-drawIntercept ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp5-drawDivide ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(Tp5-drawUnions ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
