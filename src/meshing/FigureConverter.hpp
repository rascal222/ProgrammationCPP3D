//
// Created by beugnon on 13/04/15.
//

#ifndef PROGRAMMATION3D_FIGURECONVERTER_H
#define PROGRAMMATION3D_FIGURECONVERTER_H


#include "../primitives/Cylinder.hpp"
#include "../primitives/Sphere.hpp"
#include "../primitives/Cone.hpp"
#include "../meshing/Mesh.hpp"

class FigureConverter {
public:
    static Mesh cylinderToMesh(prog_3D::Cylinder& cylinder);
    static Mesh sphereToMesh(prog_3D::Sphere& sphere);
};


#endif //PROGRAMMATION3D_FIGURECONVERTER_H
