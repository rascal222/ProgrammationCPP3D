//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"
#include "TopoPoint.h"
#include "TopoFace.h"
#include "TopoEdge.h"


TopoEdge::TopoEdge() {
}

TopoEdge::TopoEdge(TopoPoint &tp1, TopoPoint &tp2) {
    points[0]=tp1;
    points[1]=tp2;
}

TopoEdge::~TopoEdge() {
}

bool TopoEdge::havePoints(TopoPoint& p1, TopoPoint& p2)
{
    return points[0].getX()==p1.getX() && points[0].getY() == p1.getY() && points[0].getZ() == p1.getZ()
            &&  points[1].getX()==p2.getX() && points[1].getY() == p2.getY() && points[1].getZ()==p2.getZ();
}