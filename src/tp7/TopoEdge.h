//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOEDGE_H_
#define _PROGRAMMATION3D_TOPOEDGE_H_
#include <vector>
#include "core_declaration.h"


class TopoEdge
{
    std::vector<TopoFace> faces;
    std::vector<TopoPoint> points;

public:
    TopoEdge();
    TopoEdge(TopoPoint& tp1, TopoPoint& tp2);

    virtual ~TopoEdge();
    virtual std::vector<TopoFace>& getFaces(){ return faces; };
    virtual std::vector<TopoPoint>& getPoints(){ return points; };

    virtual bool havePoints(TopoPoint& p1, TopoPoint& p2);
    virtual bool havePointsIgnoreOrder(TopoPoint& p1, TopoPoint& p2) { return havePoints(p1,p2) || havePoints(p2,p1) ; }

    bool operator==(TopoEdge& edge)
    {
        return havePointsIgnoreOrder(edge.points.at(0),edge.points.at(1));
    }
};


#endif //_PROGRAMMATION3D_TOPOEDGE_H_
