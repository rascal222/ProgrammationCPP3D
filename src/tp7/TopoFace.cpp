//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"
#include <iostream>
#include <algorithm>

TopoFace::TopoFace(TopoEdge t1, TopoEdge t2, TopoEdge t3)
{
    edges.push_back(t1);
    edges.push_back(t2);
    edges.push_back(t3);
}

TopoFace::~TopoFace() {
}


prog_3D::Vector TopoFace::getNormal()
{
    std::vector<TopoPoint> vertices = getVertices();
    prog_3D::Vector v1(vertices.at(0),vertices.at(1));
    prog_3D::Vector v2(vertices.at(0),vertices.at(2));
    return v1.cross(v2);
}

std::vector<TopoPoint> TopoFace::getVertices()
{
    std::vector<TopoPoint> p;
    //TODO REMOVE DUPLICATE
    p.push_back(edges.at(0).getPoints().at(0));
    p.push_back(edges.at(0).getPoints().at(1));
    p.push_back(edges.at(1).getPoints().at(0));
    p.push_back(edges.at(1).getPoints().at(1));
    p.push_back(edges.at(2).getPoints().at(0));
    p.push_back(edges.at(2).getPoints().at(1));

   // std::sort(p.begin(),p.end());
    //auto last = std::unique(p.begin(),p.end());
    //p.erase(last,p.end());
    return p;
}