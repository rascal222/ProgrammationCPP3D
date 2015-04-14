//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"
#include <algorithm>
#include <iostream>

TopoPoint::TopoPoint(prog_3D::Point& point) : prog_3D::Point(point)
{

}

TopoPoint::~TopoPoint()
{
}

prog_3D::Vector TopoPoint::getNormal()
{
    prog_3D::Vector v;
    std::vector<TopoFace*> faces = getFaces();
    for(int i=0;i<faces.size();++i)
    {
        prog_3D::Vector v2 = faces.at(i)->getNormal();
        v2.normalize();
        v.setX(v.getX()+v2.getX());
        v.setY(v.getY()+v2.getY());
        v.setZ(v.getZ()+v2.getZ());
    }

    v.setX(v.getX()/(double)faces.size());
    v.setY(v.getY()/(double)faces.size());
    v.setZ(v.getZ()/(double)faces.size());
    v.normalize();
    return v;
}
std::vector<TopoFace*> TopoPoint::getFaces() const
{
    std::vector<TopoFace*> faces;
    for(int i=0;i<getEdges().size();++i)
        faces.insert(faces.end(),getEdges().at(i)->getFaces().begin(),getEdges().at(i)->getFaces().end());
    std::sort( faces.begin(), faces.end() );
    faces.erase( std::unique( faces.begin(), faces.end() ), faces.end() );
    return faces;
}