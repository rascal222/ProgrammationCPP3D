//
// Created by sbeugnon on 30/03/15.
//

#include <iostream>
#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"


TopoEdge::TopoEdge() {
}

TopoEdge::TopoEdge(TopoPoint* tp1, TopoPoint* tp2) {
    tp1->addEdge(this);
    tp2->addEdge(this);
    points.push_back(tp1);
    points.push_back(tp2);
}

TopoEdge::~TopoEdge() {
}

bool TopoEdge::havePoints(TopoPoint* p1, TopoPoint* p2) const
{
    return points[0] == p1 && points[1] == p2;
}


void TopoEdge::addFace(TopoFace* face)
{
    faces.push_back(face);
}

bool TopoEdge::isActiveEdge(double threshold,bool showSideOne) {
    if(getFaces().size()==2)
    {
        double rad = TopoFace::computeDihedralAngle(getFaces().at(0), getFaces().at(1));
        double degree = rad  / M_PI * 180;
        return  degree >= threshold;
    }
    else
        return showSideOne;
}
