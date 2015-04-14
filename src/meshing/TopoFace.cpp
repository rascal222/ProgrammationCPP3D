//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"
#include <iostream>
#include <algorithm>
#include <set>

TopoFace::TopoFace(TopoEdge* t1, TopoEdge* t2, TopoEdge* t3,prog_3D::Vector normal)
{
    t1->addFace(this);
    t2->addFace(this);
    t3->addFace(this);
    edges.push_back(t1);
    edges.push_back(t2);
    edges.push_back(t3);
    n = normal;

}

TopoFace::~TopoFace() {
}




prog_3D::Vector TopoFace::getNormal()
{
    if(n.norm()!=1.0)
        n.normalize();
    return n;
}

std::vector<TopoPoint*> TopoFace::getVertices()
{
    std::vector<TopoPoint*> p;

    p.push_back(getEdges().at(0)->getPoints().at(0));
    p.push_back(getEdges().at(0)->getPoints().at(1));
    p.push_back(getEdges().at(1)->getPoints().at(1));
    p.push_back(getEdges().at(1)->getPoints().at(1));
    p.push_back(getEdges().at(2)->getPoints().at(0));
    p.push_back(getEdges().at(2)->getPoints().at(1));
    std::sort(p.begin(),p.end());
    auto last = std::unique(p.begin(),p.end());
    p.erase(last,p.end());
    return p;
}

std::vector<TopoFace*> TopoFace::getNeighbours() {
    std::vector<TopoFace*> neigh;

    for(auto edge : getEdges())
        neigh.insert(neigh.end(),edge->getFaces().begin(),edge->getFaces().end());

    std::sort(neigh.begin(),neigh.end());
    neigh.erase(std::unique(neigh.begin(),neigh.end()),neigh.end());
    auto pos = std::find(neigh.begin(),neigh.end(),this);
    if(pos!=neigh.end())
        neigh.erase(pos);
    return neigh;
}

prog_3D::Point TopoFace::getCenter() {
    prog_3D::Point center;

    std::vector<TopoPoint*> s = getVertices();

    for(int i=0;i<3;++i)
        center.set(
                center.getX() + (1.0/3.0) *s.at(i)->getX(),
                center.getY() + (1.0/3.0) * s.at(i)->getY(),
                center.getZ() + (1.0/3.0) * s.at(i)->getZ());
    return center;
}
