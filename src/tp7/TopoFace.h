//
// Created by sbeugnon on 30/03/15.
//

#ifndef _PROGRAMMATION3D_TOPOFACE_H_
#define _PROGRAMMATION3D_TOPOFACE_H_
#include "core_declaration.h"
#include <vector>
#include "../core/Vector.hpp"
#include "TopoEdge.h"


class TopoFace {

private:
    std::vector<TopoEdge*> edges;
public:

    TopoFace(TopoEdge* t1,TopoEdge* t2, TopoEdge* t3);
    virtual ~TopoFace();

    virtual std::vector<TopoEdge*>& getEdges(){ return edges; }

    virtual prog_3D::Vector getNormal();

    virtual std::vector<TopoPoint*> getVertices();

};


#endif //_PROGRAMMATION3D_TOPOFACE_H_
