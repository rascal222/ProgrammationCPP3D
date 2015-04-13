//
// Created by sbeugnon on 30/03/15.
//
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


#include "../core/Point.hpp"
#include "../primitives/Sphere.hpp"
#include "../meshing/Mesh.hpp"
#include "../primitives/Cylinder.hpp"
#include "../glWrappers/GlCoreRendering.hpp"

#include "TopoMesh.h"
#include "../glWrappers/EulerCamera.hpp"
#include "../meshing/Mesh.hpp"
#include "../meshing/OffManipulator.hpp"
#include "../primitives/Sphere.hpp"




using namespace prog_3D;

int main()
{
	Mesh m;
	Point p(0,0,0);m.points.push_back(p);
	Point p1(1,1,0);m.points.push_back(p1);
	Point p2(1,-1,0);m.points.push_back(p2);

	Point p4(2,0,0);m.points.push_back(p4);

	IdTriangle id(0,2,1);m.idTriangles.push_back(id);
	IdTriangle id2(1,3,2);m.idTriangles.push_back(id2);

	TopoMesh tm(m);
    for(auto p : tm.getPoints())
    {
        std::cout << p << std::endl;
        std::cout << "in Faces: "<< p->getFaces().size() << std::endl;
        std::cout << "in Edges: "<< p->getEdges().size() << std::endl;
    }

}