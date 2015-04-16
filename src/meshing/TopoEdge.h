//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOEDGE_H_
#define _PROGRAMMATION3D_TOPOEDGE_H_
#include <vector>
#include "core_declaration.h"


class TopoEdge
{
    std::vector<TopoFace*> faces;
    std::vector<TopoPoint*> points;

public:
    TopoEdge();
    TopoEdge(TopoPoint* tp1, TopoPoint* tp2);

    virtual ~TopoEdge();
    virtual std::vector<TopoFace*>& getFaces() { return faces; };
    virtual std::vector<TopoPoint*>& getPoints() { return points; };

    virtual bool havePoint(TopoPoint* p1) const
    {
        return points[0] == p1 || points[1]==p1;
    }

    virtual bool havePoints(TopoPoint* p1, TopoPoint* p2) const;
    virtual bool havePointsIgnoreOrder(TopoPoint* p1, TopoPoint* p2) const { return havePoints(p1,p2) || havePoints(p2,p1) ; }

    bool operator==(TopoEdge& edge)
    {
        return havePointsIgnoreOrder(edge.points.at(0),edge.points.at(1));
    }

    void addFace(TopoFace* face);

    virtual bool isActiveEdge(double threshold,bool showSideOne);
};


#endif //_PROGRAMMATION3D_TOPOEDGE_H_
