//
// Created by sbeugnon on 23/03/15.
//

#include "Mesh.hpp"
#include "../core/Vector.hpp"
Mesh::Mesh() {
}
Mesh::~Mesh() {
}

float* Mesh::getPointVector()
{
    float* v = new float[3*this->points.size()];
    int index=0;
    for(int i=0;i<points.size();++i)
    {
        v[index++]=points.at(i).getX();
        v[index++]=points.at(i).getY();
        v[index++]=points.at(i).getZ();
    }
    return v;
}
unsigned int* Mesh::getIdVector()
{
    unsigned int* v = new unsigned int[3*this->idTriangles.size()];
    int index=0;
    for(int i=0;i<idTriangles.size();++i)
    {
        v[index++]=idTriangles.at(i).getPointId(0);
        v[index++]=idTriangles.at(i).getPointId(1);
        v[index++]=idTriangles.at(i).getPointId(2);
    }
    return v;
}

float* Mesh::getNormalVector()
{
    float* f = new float[3*this->idTriangles.size()];
    int index=0;
    for(int i=0;i<idTriangles.size();++i)
    {
        prog_3D::Vector v(points.at(idTriangles.at(i).getPointId(0)),points.at(idTriangles.at(i).getPointId(1)));
        prog_3D::Vector v2(points.at(idTriangles.at(i).getPointId(0)),points.at(idTriangles.at(i).getPointId(2)));
        v = v.cross(v2);
        f[index++] = v.getX();
        f[index++] = v.getY();
        f[index++] = v.getZ();
    }
    return f;
}