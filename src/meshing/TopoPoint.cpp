//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"
#include <algorithm>
#include <vector>
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

std::vector<TopoPoint *> TopoPoint::getNeighbours() const {
    std::vector<TopoPoint *> neigh;

    for(int i=0;i<getEdges().size();++i)
        neigh.insert(neigh.end(),getEdges().at(i)->getPoints().begin(),getEdges().at(i)->getPoints().end());

    std::sort(neigh.begin(),neigh.end());
    neigh.erase(std::unique(neigh.begin(),neigh.end()),neigh.end());
    const TopoPoint* thi = this;
    std::remove_if(neigh.begin(),neigh.end(),[thi](TopoPoint* tp){return tp==thi;});
    return neigh;
}

void TopoPoint::removeEdge(TopoEdge *pEdge) {
    std::remove_if(edges.begin(),edges.end(),[pEdge](TopoEdge* te){return te==pEdge;});
}
