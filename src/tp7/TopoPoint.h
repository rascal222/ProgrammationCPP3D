//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOPOINT_H_
#define _PROGRAMMATION3D_TOPOPOINT_H_

#include "core_declaration.h"
#include <vector>

#include "../core/Point.hpp"


class TopoPoint : public virtual prog_3D::Point
{
private:
    std::vector<TopoEdge> edges;
public:
    TopoPoint(Point& point);
    virtual ~TopoPoint();

    virtual void addEdge(TopoEdge& edge)
    {
        edges.push_back(edge);
    }

    virtual std::vector<TopoEdge>& getEdges()
    {
        return edges;
    }

    virtual prog_3D::Vector getNormal();
    virtual std::vector<TopoFace> getFaces();


};


#endif //_PROGRAMMATION3D_TOPOPOINT_H_
