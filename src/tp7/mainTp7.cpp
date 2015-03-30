//
// Created by sbeugnon on 30/03/15.
//
#include <iostream>
#include "../core/Point.hpp"
#include "../primitives/Sphere.hpp"
#include "../meshing/Mesh.hpp"
#include "../primitives/Cylinder.hpp"
#include "../glWrappers/GlCoreRendering.hpp"
#include <vector>
#include <algorithm>
#include "TopoMesh.h"

Mesh cylinderToMesh(prog_3D::Cylinder cylinder)
{
	Mesh m;
	std::vector<std::vector<prog_3D::Point>> matrix = cylinder.compute();
	for(unsigned int i=0;i<matrix.size();++i)
		m.points.insert(m.points.end(),matrix.at(i).begin(),matrix.at(i).end());
	int offset = matrix.at(0).size();
	std::vector<int> idTri;
	for(int i=0;i< offset;++i)
    {
//
//            prog_3D::glPoint(m.points.at(i));
		idTri.push_back(i);
		if(idTri.size()==3)
		{
			prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
			m.idTriangles.push_back(tri);
			idTri.erase(idTri.begin());//Remove first
		}
//            prog_3D::glPoint(m.points.at(offset+i));
		idTri.push_back(offset+i);
		if(idTri.size()==3)
		{
			prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
			m.idTriangles.push_back(tri);
			idTri.erase(idTri.begin());//Remove first
		}
	}
//        prog_3D::glPoint(0);
	idTri.push_back(0);
	prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
	m.idTriangles.push_back(tri);
	idTri.erase(idTri.begin());
//        prog_3D::glPoint(offset);
	idTri.push_back(offset);
	prog_3D::IdTriangle tri2(idTri.at(0),idTri.at(1),idTri.at(2));
	m.idTriangles.push_back(tri2);


	return m;
}

Mesh sphereToCylinder(prog_3D::Sphere sphere)
{
	Mesh m;

	std::vector<std::vector<prog_3D::Point>> matrix = sphere.compute();
    //TODO SPHERE TO MESH
    //NORTH POLE
    glBegin(GL_TRIANGLE_FAN);
    glPoint(matrix.at(0).at(0));
    for(int k=0;k<matrix.at(1).size();++k)
    {
        glPoint(matrix.at(1).at(k));
    }
    glPoint(matrix.at(1).at(0));
    glEnd();

    //SOUTH POLE
    glBegin(GL_TRIANGLE_FAN);
    glPoint(matrix.at(matrix.size()-1).at(0));
    for(int k=0;k<matrix.at(matrix.size()-2).size();++k)
    {
        glPoint(matrix.at(matrix.size()-2).at(k));
    }
    glPoint(matrix.at(matrix.size()-2).at(0));
    glEnd();

    for(unsigned int i=0;i<matrix.at(1).size()-1;++i)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (unsigned int k = 1; k < matrix.size()-1; ++k)
        {
            glPoint(matrix.at(k).at(i));
            glPoint(matrix.at(k).at((i+1)));
        }
        glEnd();
    }
    glBegin(GL_TRIANGLE_STRIP);
    for (unsigned int k = 1; k < matrix.size()-1; ++k)
    {
        glPoint(matrix.at(k).at(matrix.at(1).size()-1));
        glPoint(matrix.at(k).at((0)));
    }
    glEnd();

	return m;
}


int main()
{
	std::cout << "hello"<<std::endl;
	prog_3D::Point p = prog_3D::Point::Origin;
	prog_3D::Cylinder c(3,10,10,p);
	Mesh m = cylinderToMesh(c);
  //  TopoMesh tm(m);

   // std::vector<prog_3D::Point> gauss = tm.computeGaussianPointCloud();

	prog_3D::Point p2(0,0,1);
	std::cout <<"t"<< (p==prog_3D::Point::Origin) << std::endl;
}